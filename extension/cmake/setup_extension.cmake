# copy lib_src folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extension/lib_src/libtcc1_src DESTINATION ${LIBTCC_RUNTIME_TARGET_PATH})
if(WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extension/lib_src/win32/libtcc1_src DESTINATION ${LIBTCC_RUNTIME_TARGET_PATH})
endif()

# extension include directories
target_include_directories(${LIBTCC_NAME} PRIVATE extension/include/tcc extension/src
                                          PUBLIC extension/include)
