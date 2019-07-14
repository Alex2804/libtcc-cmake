file(WRITE "${CMAKE_SOURCE_DIR}/include/tcc/config.h" "#define TCC_VERSION \"${TCC_VERSION}\"
#ifdef TCC_TARGET_X86_64
    #define TCC_LIBTCC1 \"libtcc1-64.a\"
#else
    #define TCC_LIBTCC1 \"libtcc1-32.a\"
#endif")