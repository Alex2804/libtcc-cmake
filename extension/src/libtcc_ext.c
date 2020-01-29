#include "tcc/tcc.h" // must be included before libtcc_ext.h for correct definition of LIBTCCAPI
#if ONE_SOURCE
# include "tcctools.c"
#else
ST_FUNC int tcc_tool_ar(TCCState *s, int argc, char **argv);
#endif

#include "tcc/libtcc_ext.h"

#include <string.h>
#include <stdio.h>

#include "private/utility.h"
#include "private/filesystem.h"

typedef struct {
    TCCErrorFunc error_function;
    void* error_opaque;

    const char* libtcc1_name;
    const char* libtcc1_src_path;
    const char* libtcc1_obj_path;
    const char* libtcc1_dest_path;

    const char* sys_include_path;
    const char* include_path;
} ATccExtensionVariables;

static ATccExtensionVariables aTccExtensionVariables = {NULL, NULL,
                                                        TCC_LIBTCC1, ALIBTCC1_SRC_PATH, ALIBTCC1_OBJ_PATH, ALIBTCC1_DEST_PATH,
                                                        "/usr/include", ALIBTCC_INCLUDE_PATH};

void atcc_set_filetype(TCCState* tccState, const char* fileExtension)
{
    if (tccState != NULL && fileExtension != NULL) {
        if (!strcmp(fileExtension, "S"))
            tccState->filetype = AFF_TYPE_ASMPP;
        else if (!strcmp(fileExtension, "s"))
            tccState->filetype = AFF_TYPE_ASM;
        else if (!PATHCMP(fileExtension, "c") || !PATHCMP(fileExtension, "i"))
            tccState->filetype = AFF_TYPE_C;
        else
            tccState->filetype |= AFF_TYPE_BIN;
    }
}

void atcc_configure_state(TCCState* state)
{
    if(state != NULL) {
        if(aTccExtensionVariables.error_function != NULL)
            tcc_set_error_func(state, aTccExtensionVariables.error_opaque, aTccExtensionVariables.error_function);

        if(aTccExtensionVariables.libtcc1_dest_path != NULL)
            tcc_set_lib_path(state, aTccExtensionVariables.libtcc1_dest_path);

        if(aTccExtensionVariables.sys_include_path != NULL)
            tcc_add_sysinclude_path(state, aTccExtensionVariables.sys_include_path);
        if(aTccExtensionVariables.include_path != NULL)
            tcc_add_include_path(state, aTccExtensionVariables.include_path);
    }
}

TCCState* atcc_new()
{
    FILE *libtcc1_file;
    char *libtcc1_path;
    TCCState* state;

    libtcc1_path = (char*) tcc_malloc((strlen(aTccExtensionVariables.libtcc1_dest_path) + strlen(aTccExtensionVariables.libtcc1_name) + 1) * sizeof(char));
    strcpy(libtcc1_path, aTccExtensionVariables.libtcc1_dest_path);
    strcat(libtcc1_path, aTccExtensionVariables.libtcc1_name);
    libtcc1_file = fopen(libtcc1_path, "r");
    tcc_free(libtcc1_path);

    if (!libtcc1_file) {
        if (atcc_build_libtcc1() != 0)
            return NULL;
    } else {
        fclose(libtcc1_file);
    }

    state = tcc_new();
    atcc_configure_state(state);
    return state;
}

int atcc_make_ar(const char *name, int file_count, char **files)
{
    size_t i;
    int argc = file_count + 2;
    int result;
    char** argv = (char**) tcc_malloc(argc * sizeof(char*));

    argv[0] = tcc_strdup("rcs");
    argv[1] = tcc_strdup(name);
    for(i = 0; i < file_count; i++) {
        argv[i + 2] = files[i];
    }
    result = tcc_tool_ar(NULL, argc, argv);
    tcc_free(argv[0]);
    tcc_free(argv[1]);
    tcc_free(argv);
    return result;
}

int atcc_build_libtcc1()
{
    TCCState *state;
    char** splitted_name;
    char** src_names;
    char** obj_names;
    char** splitted_file_name;
    char* file_name;
    char* file_content;
    int file_count;
    int result;
    size_t i;
    size_t j;

    result = atcc_create_dir_recursive(aTccExtensionVariables.libtcc1_dest_path);
    if(result == 0 && strcmp(aTccExtensionVariables.libtcc1_dest_path, aTccExtensionVariables.libtcc1_obj_path) != 0)
        atcc_create_dir_recursive(aTccExtensionVariables.libtcc1_obj_path);

    state = tcc_new();
    atcc_configure_state(state);

    if((result = tcc_set_output_type(state, TCC_OUTPUT_OBJ)) != 0) {
        tcc_delete(state);
        return result;
    }

    src_names = atcc_get_libtcc1_files();
    file_count = atcc_splitted_string_length(src_names);
    obj_names = (char**) tcc_malloc(file_count * sizeof(char*));

    for(i = 0; i < file_count; i++) {
        splitted_file_name = atcc_split_string(src_names[i], '.');
        file_name = atcc_concatenate_path(aTccExtensionVariables.libtcc1_src_path, splitted_file_name[0], splitted_file_name[1]);
        result = tcc_add_file(state, file_name);
        tcc_free(file_name);
        if(result) {
            atcc_free_splitted_string(splitted_file_name);
            atcc_free_splitted_string(src_names);
            for(j = 0; j < i; j++) {
                remove(obj_names[i]);
                tcc_free(obj_names[j]);
            }
            tcc_free(obj_names);
            tcc_delete(state);
            return result;
        }

        file_name = atcc_concatenate_path(aTccExtensionVariables.libtcc1_obj_path, splitted_file_name[0], "o");
        obj_names[i] = file_name;
        result = tcc_output_file(state, file_name);
        atcc_free_splitted_string(splitted_file_name);
        if(result) {
            atcc_free_splitted_string(src_names);
            for(j = 0; j < i+1; j++) {
                tcc_free(obj_names[j]);
            }
            tcc_free(obj_names);
            tcc_delete(state);
            return result;
        }
    }

    splitted_name = atcc_split_string(aTccExtensionVariables.libtcc1_name, '.');
    file_name = atcc_concatenate_path(aTccExtensionVariables.libtcc1_dest_path, splitted_name[0], "a");
    atcc_free_splitted_string(splitted_name);
    result = atcc_make_ar(file_name, file_count, obj_names);
    tcc_free(file_name);

    atcc_free_splitted_string(src_names);
    for(i = 0; i < file_count; i++) {
        remove(obj_names[i]);
        tcc_free(obj_names[i]);
    }
    tcc_free(obj_names);
    tcc_delete(state);

    return result;
}

void atcc_set_error_func(void* error_opaque, TCCErrorFunc error_func)
{
    aTccExtensionVariables.error_function = error_func;
    aTccExtensionVariables.error_opaque = error_opaque;
}
void atcc_set_include_path(const char* path)
{
    aTccExtensionVariables.include_path = path == NULL ? ALIBTCC_INCLUDE_PATH : path;
}

void atcc_set_libtcc1_name(const char* name)
{
    aTccExtensionVariables.libtcc1_name = name == NULL ? TCC_LIBTCC1 : name;
}
void atcc_set_libtcc1_src_path(const char* path)
{
    aTccExtensionVariables.libtcc1_src_path = path == NULL ? ALIBTCC1_SRC_PATH : path;
}
void atcc_set_libtcc1_obj_path(const char* path)
{
    aTccExtensionVariables.libtcc1_obj_path = path == NULL ? ALIBTCC1_OBJ_PATH : path;
}
void atcc_set_libtcc1_dest_path(const char* path)
{
    aTccExtensionVariables.libtcc1_dest_path = path == NULL ? ALIBTCC1_DEST_PATH : path;
}
