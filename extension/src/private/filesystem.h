#ifndef LIBTCC_FILESYSTEM_H
#define LIBTCC_FILESYSTEM_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* creates a directory for the given path recursive */
int atcc_create_dir_recursive(const char* path);

/* copy a directory for the given path */
char* atcc_get_file_content(const char* path);

#ifdef __cplusplus
}
#endif

#endif //LIBTCC_FILESYSTEM_H
