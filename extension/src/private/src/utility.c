#include "../utility.h"

#include <string.h>

#include "../../../../src/tcc.h"

char* atcc_concatenate_path(const char* path, const char* filename, const char* extension)
{
    char* fpath;
    char* concatenated;
    size_t length, i, fpath_length = 0;
    size_t filename_length;
    size_t extension_length;
    char current_char, last_char;
    if(path == NULL || filename == NULL)
        return NULL;
    filename_length = strlen(filename);
    length = (extension == NULL) ? 0 : strlen(extension);
    extension_length = (length == 0) ? 0 : length + 1;
    // format path
    length = strlen(path);
    last_char = '\0';
    fpath = (char*) tcc_malloc((length + 1) * sizeof(char));
    for(i = 0; i < length; ++i) {
        current_char = path[i];
        if(current_char != '/' || last_char != '/')
            fpath[fpath_length++] = current_char;
        last_char = current_char;
    }
    fpath_length = fpath_length;
    if(last_char != '/')
        fpath[fpath_length++] = '/'; // always '/' as last char of path
    // create new string
    concatenated = (char*)tcc_realloc(fpath, (fpath_length + filename_length + extension_length + 1) * sizeof(char));
    memcpy(concatenated + fpath_length, filename, filename_length);
    if(extension_length > 0) {
        concatenated[fpath_length + filename_length] = '.';
        memcpy(concatenated + fpath_length + filename_length + 1, extension, extension_length - 1);
    }
    concatenated[fpath_length + filename_length + extension_length] = '\0';
    return concatenated;
}

char** atcc_split_string(const char* string, char delimiter)
{
    size_t size, skippable_delimiters = 0;
    int segment_count = 0;
    char* tmp_string;
    char** splitted;
    size_t i, index = 0, src_offset = 0, dest_offset = 0;
    char current_char, last_char = delimiter;

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
    return atcc_split_string(ALIBTCC1_SOURCES, ':');
}