#include "../utility.h"

#include <string.h>

#include "tcc/tcc.h"

char* atcc_concatenate_path(const char* path, const char* file, const char* extension)
{
    if(path == NULL || file == NULL)
        return NULL;
    size_t file_extension_size = extension == NULL ? 0 : strlen(extension);
    size_t extra_size = file_extension_size > 0 ? 2 : 1; // only '\0' if file_extension_size is zero or '.' and '\0 if not
    char* concatenatedPath = (char*) tcc_malloc((strlen(path) + strlen(file) + file_extension_size + extra_size) * sizeof(char));
    strcpy(concatenatedPath, path);
    strcat(concatenatedPath, file);
    if(file_extension_size > 0) {
        strcat(concatenatedPath, ".");
        strcat(concatenatedPath, extension);
    }
    strcat(concatenatedPath, "\0");
    return concatenatedPath;
}

char** atcc_split_string(const char* string, char delimiter)
{
    size_t size;
    size_t skippable_delimiters = 0;
    int segment_count = 0;
    char* tmp_string;
    char** splitted;
    size_t index = 0;
    size_t src_offset = 0;
    size_t dest_offset = 0;
    char current_char;
    char last_char = delimiter;
    size_t i;

    if(string == NULL || string[0] == '\0')
        return NULL;

    for(size = 0; (current_char = string[size]) != '\0'; ++size) {
        if(current_char == delimiter) {
            if(last_char != delimiter)
                ++segment_count;
            else
                ++skippable_delimiters;
        }
        last_char = current_char;
    }
    if(string[size - 1] != delimiter)
        ++segment_count;
    else
        ++skippable_delimiters;
    tmp_string = (char*) tcc_malloc((size - skippable_delimiters + 1) * sizeof(char));
    splitted = (char**) tcc_malloc((segment_count + 1) * sizeof(char*));
    if(tmp_string == NULL || splitted == NULL) {
        tcc_free(tmp_string);
        return NULL;
    }

    last_char = delimiter;
    for(i = 0; i < size + 1; ++i) {
        current_char = string[i];
        if(current_char == delimiter || current_char == '\0') {
            if(last_char != delimiter) {
                size_t segment_size = i - src_offset;
                memcpy(tmp_string + dest_offset, string + src_offset, segment_size);
                splitted[index++] = tmp_string + dest_offset;
                dest_offset += segment_size;
                src_offset = i;
                tmp_string[dest_offset++] = '\0';
            }
            ++src_offset;
        }
        last_char = current_char;
    }
    splitted[index] = NULL;

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