#ifndef LIBTCC_FILESYSTEM_H
#define LIBTCC_FILESYSTEM_H

#include <stdlib.h>

#ifdef __ANDROID__
#include <jni.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* creates a directory for the given path recursive, returns -1 on failure */
int atcc_create_dir_recursive(const char* path);

#ifdef __ANDROID__
/* sets the asset manager to load files from, returns -1 on failure */
int atcc_set_asset_manager(JNIEnv* env, jobject manager);
#endif

/* copy a directory for the given path, returns NULL on failure */
char* atcc_get_file_content(const char* path);

#ifdef __cplusplus
}
#endif

#endif //LIBTCC_FILESYSTEM_H
