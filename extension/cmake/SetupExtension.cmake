# copy lib_libtcc1 folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extension/lib_src/lib_libtcc1 DESTINATION ${CMAKE_BINARY_DIR})
if(WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extension/lib_src/win32/lib_libtcc1 DESTINATION ${CMAKE_BINARY_DIR})
endif()

# include extension include directories
target_include_directories(${LIBTCC_NAME} PRIVATE extension/include/tcc extension/src
                                          PUBLIC extension/include)

list(APPEND LIBTCC_COMPILE_DEFINITIONS "ALIBTCC_ENABLE_EXTENSION")

if(NOT DEFINED LIBTCC1_SRC_PATH)
    set(LIBTCC1_SRC_PATH "lib_libtcc1/")
endif()
list(APPEND LIBTCC_COMPILE_DEFINITIONS "ALIBTCC1_SRC_PATH=\"${LIBTCC1_SRC_PATH}\"")
if(DEFINED LIBTCC1_DEST_PATH)
    list(APPEND LIBTCC_COMPILE_DEFINITIONS "ALIBTCC1_DEST_PATH=\"${LIBTCC1_DEST_PATH}\"")
endif()
if(DEFINED LIBTCC1_OBJ_PATH)
    list(APPEND LIBTCC_COMPILE_DEFINITIONS "ALIBTCC1_OBJ_PATH=\"${LIBTCC1_OBJ_PATH}\"")
endif()
if(DEFINED LIBTCC_INCLUDE_PATH)
    list(APPEND LIBTCC_COMPILE_DEFINITIONS "ALIBTCC_INCLUDE_PATH=\"${LIBTCC_INCLUDE_PATH}\"")
endif()