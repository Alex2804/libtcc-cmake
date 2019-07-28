# cleanup
file(REMOVE_RECURSE "${TCC_RUNTIME_TARGET_DIR}/lib/tcc")

# copy include directories
file(COPY "include" DESTINATION "${TCC_RUNTIME_TARGET_DIR}/lib/tcc")
if(WIN32)
    file(COPY "win32/include" DESTINATION "${TCC_RUNTIME_TARGET_DIR}/lib/tcc")
endif()

# copy libtcc1-32.a
file(COPY "lib/lib_${TCC_TARGET_ARCHITECTURE}" DESTINATION "${TCC_RUNTIME_TARGET_DIR}/lib/tcc")
file(RENAME "${TCC_RUNTIME_TARGET_DIR}/lib/tcc/lib_${TCC_TARGET_ARCHITECTURE}" "${TCC_RUNTIME_TARGET_DIR}/lib/tcc/lib")
