# cleanup
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/lib/tcc")

# copy include directories
file(COPY "include" DESTINATION "${CMAKE_BINARY_DIR}/lib/tcc")
if(WIN32)
    file(COPY "win32/include" DESTINATION "${CMAKE_BINARY_DIR}/lib/tcc")
endif()

# copy libtcc1*.a
file(COPY "lib/lib_${TCC_TARGET_ARCHITECTURE}" DESTINATION "${CMAKE_BINARY_DIR}/lib/tcc")
file(RENAME "${CMAKE_BINARY_DIR}/lib/tcc/lib_${TCC_TARGET_ARCHITECTURE}" "${CMAKE_BINARY_DIR}/lib/tcc/lib")