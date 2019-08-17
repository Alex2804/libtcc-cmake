#include "extension/include/tcc/libtcc_ext.h"

#include "tcctools.c"
#include "libtcc_ext_tools.c"

static int a_alibtcc_extension_is_compiling = 0;

int alibtcc_extension_is_compiling() {
    return a_alibtcc_extension_is_compiling;
}

int tcc_make_ar(const char *name, int fileCount, char **files)
{
    int argc = fileCount + 2;
    char** argv = (char**) tcc_malloc(argc * sizeof(char*));
    int result;

    argv[0] = tcc_strdup("rcs");
    argv[1] = tcc_strdup(name);
    for(int i = 0; i < fileCount; i++) {
        argv[i + 2] = files[i];
    }
    result = tcc_tool_ar(NULL, argc, argv);
    tcc_free(argv[0]);
    tcc_free(argv[1]);
    tcc_free(argv);
    return result;
}

#define _ALIBTCC_BUILD_LIBTCC1_VALIDATE_RESULT_ if(result) {\
tcc_delete(tccState);\
return result;\
}

int tcc_build_libtcc1_default()
{
    return tcc_build_libtcc1(TCC_LIBTCC1, ALIBTCC1_DEST_PATH, ALIBTCC1_SRC_PATH);
}

int tcc_build_libtcc1(const char* name, const char* destPath, const char* srcPath)
{
    TCCState *tccState;
#ifdef ALIBTCC1_OBJ_PATH
    const char* obj_path = ALIBTCC1_OBJ_PATH;
#else
    const char* obj_path = destPath;
#endif

    char** splitted_name;
    char** src_names;
    char** obj_names;
    char** splitted_file_name;
    char* file_name;
    int file_count;
    int result;

    atcc_create_dir(obj_path);
    atcc_create_dir(destPath);

    a_alibtcc_extension_is_compiling = 1;

    tccState = tcc_new();

#ifndef WIN32
    result = tcc_add_include_path(tccState, "/usr/include");
    _ALIBTCC_BUILD_LIBTCC1_VALIDATE_RESULT_
#endif
    result = tcc_add_include_path(tccState, "include");
    _ALIBTCC_BUILD_LIBTCC1_VALIDATE_RESULT_

    result = tcc_set_output_type(tccState, TCC_OUTPUT_OBJ);
    _ALIBTCC_BUILD_LIBTCC1_VALIDATE_RESULT_

    src_names = atcc_get_libtcc1_files();
    file_count = atcc_splitted_string_length(src_names);
    obj_names = (char**) tcc_malloc(file_count * sizeof(char*));

    for(int i = 0; i < file_count; i++) {
        splitted_file_name = atcc_split_string(src_names[i], '.');
        file_name = atcc_concat_path(srcPath, splitted_file_name[0], splitted_file_name[1]);
        result = tcc_add_file(tccState, file_name);
        tcc_free(file_name);
        if(result) {
            atcc_free_splitted_string(splitted_file_name);
            atcc_free_splitted_string(src_names);
            for(int j = 0; j < i; j++) {
                tcc_free(obj_names[j]);
            }
            tcc_free(obj_names);
            tcc_delete(tccState);
            return result;
        }

        file_name = atcc_concat_path(obj_path, splitted_file_name[0], "o");
        obj_names[i] = file_name;
        result = tcc_output_file(tccState, file_name);
        atcc_free_splitted_string(splitted_file_name);
        if(result) {
            atcc_free_splitted_string(src_names);
            for(int j = 0; j < i+1; j++) {
                tcc_free(obj_names[j]);
            }
            tcc_free(obj_names);
            tcc_delete(tccState);
            return result;
        }
    }

    splitted_name = atcc_split_string(name, '.');
    file_name = atcc_concat_path(destPath, splitted_name[0], "a");
    atcc_free_splitted_string(splitted_name);
    result = tcc_make_ar(file_name, file_count, obj_names);
    tcc_free(file_name);

    for(int i = 0; i < file_count; i++) {
        remove(obj_names[i]);
    }

    atcc_free_splitted_string(src_names);
    for(int i = 0; i < file_count; i++) {
        tcc_free(obj_names[i]);
    }
    tcc_free(obj_names);
    tcc_delete(tccState);

    a_alibtcc_extension_is_compiling = 0;

    return result;
}
