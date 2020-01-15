#ifndef ALIBTCC_LIBTCC_EXT_H
#define ALIBTCC_LIBTCC_EXT_H

#include "tcc/libtcc.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ALIBTCC1_SRC_PATH
#error "ALIBTCC1_SRC_PATH must be defined if you wish to use the libtcc extension"
#endif
#ifndef ALIBTCC1_DEST_PATH
# define AALIBTCC1_DEST_PATH "lib/"
#endif

/* create a new TCC compilation context and sets include and lib paths if possible */
LIBTCCAPI TCCState* atcc_new();

/* build ar archives with tiny_libmaker. Returns 0 on success, another value on failure */
LIBTCCAPI int atcc_make_ar(const char* name, int fileCount, char** files);

/* build libtcc1.a, returns 0 on success, another value on failure */
LIBTCCAPI int atcc_build_libtcc1_default();
LIBTCCAPI int atcc_build_libtcc1(const char* name, const char* destPath, const char* srcPath);

/* set error/warning display callback for every TCCState created with atcc_new */
LIBTCCAPI void atcc_set_error_func(void *error_opaque, TCCErrorFunc error_func);

#ifdef __cplusplus
}
#endif

#endif //ALIBTCC_LIBTCC_EXT_H
