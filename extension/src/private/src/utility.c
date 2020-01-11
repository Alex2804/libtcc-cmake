#include "../utility.h"

#include <string.h>

#include "tcc/tcc.h"

char* atcc_concatenate_path(const char* prefixPath, const char* fileName, const char* fileExtension)
{
    char* path;
    size_t extra_size;
    size_t file_extension_size = strlen(fileExtension);
    if(file_extension_size == 0)
        extra_size = 1; // only '\0'
    else
        extra_size = 2; // '.' and '\0'
    path = (char*) tcc_malloc((strlen(prefixPath) + strlen(fileName) + strlen(fileExtension) + extra_size) * sizeof(char));
    strcpy(path, prefixPath);
    strcat(path, fileName);
    if(strlen(fileExtension) > 0) {
        strcat(path, ".");
        strcat(path, fileExtension);
    }
    strcat(path, "\0");
    return path;
}

char** atcc_split_string(const char* string, char delimiter)
{
    size_t size;
    int delimiterCount = 0;
    char* tmpString;
    char** splitted;
    size_t index = 0;
    size_t offset = 0;

    if(string == NULL)
        return NULL;

    for(size = 0; string[size] != '\0'; ++size) {
        if(string[size] == delimiter)
            delimiterCount++;
    }

    if(size == 0)
        return NULL;

    tmpString = (char*) tcc_malloc((size + 1) * sizeof(char));
    memcpy(tmpString, string, size);
    tmpString[size] = '\0';

    splitted = (char**) tcc_malloc((delimiterCount + 2) * sizeof(char*));

    for(size = 0; tmpString[size] != '\0'; ++size) {
        if(tmpString[size] == delimiter) {
            tmpString[size] = '\0';
            splitted[index++] = tmpString + (offset * sizeof(char));
            offset = size + 1;
        }
    }
    splitted[index] = tmpString + (offset * sizeof(char));
    splitted[delimiterCount + 1] = NULL;

    return splitted;
}

size_t atcc_splitted_string_length(char** s)
{
    size_t i = 0;
    if(s != NULL)
        for(; s[i] != NULL; ++i);
    return i;
}

void atcc_free_splitted_string(char** splitted)
{
    if(splitted != NULL) {
        tcc_free(splitted[0]);
        tcc_free(splitted);
    }
}

char** atcc_get_libtcc1_files()
{
#ifdef TCC_TARGET_PE
    #ifdef TCC_TARGET_I386
        return atcc_split_string("libtcc1.c;alloca86.S;alloca86-bt.S;chkstk.S;bcheck.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c", ';');
    #elif defined TCC_TARGET_X86_64
        return atcc_split_string("libtcc1.c;alloca86_64.S;alloca86_64-bt.S;chkstk.S;bcheck.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c", ';');
    #elif defined TCC_TARGET_ARM
        return atcc_split_string("libtcc1.c;armeabi.c;alloca-arm.S;armflush.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c", ';');
    #endif
#elif defined(TCC_TARGET_MACHO)
    #ifdef TCC_TARGET_X86_64
        return atcc_split_string("libtcc1.c;alloca86_64.S;alloca86_64-bt.S;va_list.c", ';');
    #endif
#else
    #ifdef TCC_TARGET_I386
        return atcc_split_string("libtcc1.c;alloca86.S;alloca86-bt.S;bcheck.c;dsohandle.c", ';');
    #elif defined TCC_TARGET_X86_64
        return atcc_split_string("libtcc1.c;alloca86_64.S;alloca86_64-bt.S;va_list.c;bcheck.c;dsohandle.c", ';');
    #elif defined TCC_TARGET_ARM
        return atcc_split_string("libtcc1.c;armeabi.c;alloca-arm.S;armflush.c;dsohandle.c", ';');
    #elif defined TCC_TARGET_ARM64
        return atcc_split_string("lib-arm64.c;dsohandle.c", ';');
    #endif
#endif
}

/*
#define TCC_I366_SOURCE_FILES "libtcc1.c;alloca86.S;alloca86-bt.S"
#define TCC_X86_64_SOURCE_FILES "libtcc1.c;alloca86_64.S;alloca86_64-bt.S"
#define TCC_ARM_SOURCE_FILES "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
#define TCC_ARM64_SOURCE_FILES "lib-arm64.c"
#define TCC_WIN_SOURCE_FILES "crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c"

OBJ-i386 = "libtcc1.c;alloca86.S;alloca86-bt.S;bcheck.c"
OBJ-x86_64 = "libtcc1.c;alloca86_64.S;alloca86_64-bt.S;va_list.c;bcheck.c"
OBJ-x86_64-osx = "libtcc1.c;alloca86_64.S;alloca86_64-bt.S;va_list.c"
OBJ-i386-win32 = "libtcc1.c;alloca86.S;alloca86-bt.S;chkstk.S;bcheck.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c"
OBJ-x86_64-win32 = "libtcc1.c;alloca86_64.S;alloca86_64-bt.S;chkstk.S;bcheck.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c"
OBJ-arm64 = "lib-arm64.c"
OBJ-arm = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-fpa = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-fpa-ld = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-vfp = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-eabi = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-eabihf = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-wince = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c"
 */