#ifndef LIBTCC_UTILITY_H
#define LIBTCC_UTILITY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* creates a new string and concatenates the passed to prefixPath + fileName + "." + fileExtension + "\0"  */
char* atcc_concatenate_path(const char* prefixPath, const char* fileName, const char* fileExtension);

/* returns a NULL terminated array with the passed string splitted at delimiter (delimiters are excluded) */
char** atcc_split_string(const char* string, char delimiter);
/* returns the length of an splitted string array. The passed array must be NULL terminated */
size_t atcc_splitted_string_length(char** s);
/* free the memory of a splitted string) */
void atcc_free_splitted_string(char** splitted);

/* returns an array (must be freed with atcc_free_splitted) with all files which are required for libtcc1.a */
char** atcc_get_libtcc1_files();

#ifdef __cplusplus
}
#endif

#endif //LIBTCC_UTILITY_H
