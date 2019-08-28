# copy lib_libtcc1 folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extension/lib_src/lib_libtcc1 DESTINATION ${LIBTCC_RUNTIME_TARGET_DIR})
if(WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extension/lib_src/win32/lib_libtcc1 DESTINATION ${LIBTCC_RUNTIME_TARGET_DIR})
endif()

target_include_directories(${LIBTCC_NAME} PRIVATE extension/include/tcc extension/src)
target_include_directories(${LIBTCC_NAME} PUBLIC extension/include)

if(NOT DEFINED LIBTCC1_DEST_PATH)
    set(LIBTCC1_DEST_PATH ${LIBTCC_RUNTIME_TARGET_DIR}/lib/)
endif()
if(NOT DEFINED LIBTCC1_SRC_PATH)
    set(LIBTCC1_SRC_PATH ${LIBTCC_RUNTIME_TARGET_DIR}/lib_libtcc1/)
endif()

list(APPEND LIBTCC_COMPILE_DEFINITIONS
        "ALIBTCC_ENABLE_EXTENSION"
        "ALIBTCC1_DEST_PATH=\"${LIBTCC1_DEST_PATH}\""
        "ALIBTCC1_SRC_PATH=\"${LIBTCC1_SRC_PATH}\""
        "ALIBTCC_INCLUDE_PATH=\"${LIBTCC_RUNTIME_TARGET_DIR}/include\"")