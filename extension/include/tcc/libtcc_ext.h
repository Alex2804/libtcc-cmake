#ifndef ALIBTCC_LIBTCC_EXT_H
#define ALIBTCC_LIBTCC_EXT_H

#include "libtcc.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ALIBTCC1_SOURCE_PATH
# define ALIBTCC1_SOURCE_PATH ""
#endif

#ifndef ALIBTCC1_DESTINATION_PATH
# define ALIBTCC1_DESTINATION_PATH ""
#endif

/* build ar archives */
LIBTCCAPI int tcc_make_ar(const char *name, int fileCount, char** files);

/*****************************/
/* build libtcc1.a, returns 0 if all is ok, another value if something failed */
LIBTCCAPI int tcc_build_libtcc1_default();
LIBTCCAPI int tcc_build_libtcc1(const char* name, const char* destPath, const char* srcPath);


#ifdef __cplusplus
}
#endif

#endif //ALIBTCC_LIBTCC_EXT_H
