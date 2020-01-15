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

#ifndef ALIBTCC_INCLUDE_PATH
# define ALIBTCC_INCLUDE_PATH "include"
#endif

TCCErrorFunc atccErrorFunction = NULL;
void* atccErrorOpaque = NULL;

TCCState* atcc_new()
{
    TCCState *tccState;
    int result;
    FILE *libtcc1_file;
    char *libtcc1_path;
    size_t path_length;
    size_t name_length;

    path_length = strlen(ALIBTCC1_DEST_PATH);
    name_length = strlen(TCC_LIBTCC1);

    libtcc1_path = (char *) tcc_malloc((path_length + name_length + 1) * sizeof(char));
    strcpy(libtcc1_path, ALIBTCC1_DEST_PATH);
    strcat(libtcc1_path, TCC_LIBTCC1);
    libtcc1_file = fopen(libtcc1_path, "r");
    tcc_free(libtcc1_path);

    if (!libtcc1_file) {
        result = atcc_build_libtcc1_default();
        if (result) {
            return NULL;
        }
    } else {
        fclose(libtcc1_file);
    }

    tccState = tcc_new();
    if(atccErrorFunction != NULL)
        tcc_set_error_func(tccState, atccErrorOpaque, atccErrorFunction);

    tcc_add_include_path(tccState, ALIBTCC_INCLUDE_PATH);

#ifdef ALIBTCC1_DEST_PATH
    tcc_add_library_path(tccState, ALIBTCC1_DEST_PATH);
    tcc_set_lib_path(tccState, ALIBTCC1_DEST_PATH);
#endif

    return tccState;
}

int atcc_make_ar(const char *name, int fileCount, char **files)
{
    size_t i;
    int argc = fileCount + 2;
    int result;
    char** argv = (char**) tcc_malloc(argc * sizeof(char*));

    argv[0] = tcc_strdup("rcs");
    argv[1] = tcc_strdup(name);
    for(i = 0; i < fileCount; i++) {
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

int atcc_build_libtcc1_default()
{
    return atcc_build_libtcc1(TCC_LIBTCC1, ALIBTCC1_DEST_PATH, ALIBTCC1_SRC_PATH);
}

int atcc_build_libtcc1(const char* name, const char* destPath, const char* srcPath)
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
    size_t i;
    size_t j;

    atcc_create_dir_recursive(obj_path);
    atcc_create_dir_recursive(destPath);

    tccState = tcc_new();
    if(atccErrorFunction != NULL)
        tcc_set_error_func(tccState, atccErrorOpaque, atccErrorFunction);

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

    for(i = 0; i < file_count; i++) {
        splitted_file_name = atcc_split_string(src_names[i], '.');
        file_name = atcc_concatenate_path(srcPath, splitted_file_name[0], splitted_file_name[1]);
        result = tcc_add_file(tccState, file_name);
        tcc_free(file_name);
        if(result) {
            atcc_free_splitted_string(splitted_file_name);
            atcc_free_splitted_string(src_names);
            for(j = 0; j < i; j++) {
                tcc_free(obj_names[j]);
            }
            tcc_free(obj_names);
            tcc_delete(tccState);
            return result;
        }

        file_name = atcc_concatenate_path(obj_path, splitted_file_name[0], "o");
        obj_names[i] = file_name;
        result = tcc_output_file(tccState, file_name);
        atcc_free_splitted_string(splitted_file_name);
        if(result) {
            atcc_free_splitted_string(src_names);
            for(j = 0; j < i+1; j++) {
                tcc_free(obj_names[j]);
            }
            tcc_free(obj_names);
            tcc_delete(tccState);
            return result;
        }
    }

    splitted_name = atcc_split_string(name, '.');
    file_name = atcc_concatenate_path(destPath, splitted_name[0], "a");
    atcc_free_splitted_string(splitted_name);
    result = atcc_make_ar(file_name, file_count, obj_names);
    tcc_free(file_name);

    for(i = 0; i < file_count; i++) {
        remove(obj_names[i]);
    }

    atcc_free_splitted_string(src_names);
    for(i = 0; i < file_count; i++) {
        tcc_free(obj_names[i]);
    }
    tcc_free(obj_names);
    tcc_delete(tccState);

    return result;
}

void atcc_set_error_func(void* error_opaque, TCCErrorFunc error_func)
{
    atccErrorFunction = error_func;
    atccErrorOpaque = error_opaque;
}
