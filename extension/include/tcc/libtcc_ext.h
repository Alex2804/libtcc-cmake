#ifndef ALIBTCC_LIBTCC_EXT_H
#define ALIBTCC_LIBTCC_EXT_H

#include "libtcc.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ALIBTCC1_SRC_PATH
#error "ALIBTCC1_SRC_PATH must be defined if you wish to use the libtcc extension"
#endif
#ifndef ALIBTCC1_DEST_PATH
#error "ALIBTCC1_DEST_PATH must be defined if you wish to use the libtcc extension"
#endif

/* creates new TCCState and sets include/lib path if possible */
LIBTCCAPI TCCState* atcc_new();

/*****************************/
/* build ar archives with tinyp_libmaker*/
LIBTCCAPI int tcc_make_ar(const char *name, int fileCount, char** files);

/*****************************/
/* build libtcc1.a, returns 0 if all is ok, another value if something failed */
LIBTCCAPI int tcc_build_libtcc1_default();
LIBTCCAPI int tcc_build_libtcc1(const char* name, const char* destPath, const char* srcPath);

#ifdef __cplusplus
}
#endif

#endif //ALIBTCC_LIBTCC_EXT_H
