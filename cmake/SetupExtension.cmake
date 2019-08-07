# copy lib_libtcc1 folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extension/lib_src/lib_libtcc1 DESTINATION ${LIBTCC_RUNTIME_TARGET_DIR})
if(WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/extension/lib_src/win32/lib_libtcc1 DESTINATION ${LIBTCC_RUNTIME_TARGET_DIR})
endif()

target_include_directories(${LIBTCC_NAME} PRIVATE ../extension/include/tcc ../extension/src extension/include/tcc extension/src)
target_include_directories(${LIBTCC_NAME} PUBLIC ../extension/include extension/include)

list(APPEND LIBTCC_COMPILE_DEFINITIONS "ALIBTCC_ENABLE_EXTENSION" "ALIBTCC1_DESTINATION_PATH=\"lib/\"" "ALIBTCC1_SOURCE_PATH=\"lib_libtcc1/\"")