set(TCC_CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/tcc/config.h")

message("generating tcc config.h in \"${TCC_CONFIG_DIR}\" ...")
file(WRITE ${TCC_CONFIG_DIR} "#define TCC_VERSION \"${TCC_VERSION}\"
#ifdef TCC_TARGET_X86_64
    #define TCC_LIBTCC1 \"libtcc1-64.a\"
#else
    #define TCC_LIBTCC1 \"libtcc1-32.a\"
#endif")
message("generated tcc config.h!")