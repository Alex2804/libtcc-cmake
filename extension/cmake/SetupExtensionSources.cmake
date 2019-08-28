# This file must be included in the main CMakeLists.txt before the compilation of libtcc to inject extension sources
list(APPEND LIBTCC_SOURCES "extension/src/libtcc_ext.c")