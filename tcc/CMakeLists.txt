cmake_minimum_required(VERSION 3.14)
project(tcc C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${TCC_RUNTIME_TARGET_DIR}")
add_executable(TinyCCompiler ../src/tcc.c)

target_include_directories(TinyCCompiler PRIVATE ../include/tcc ../src)
target_include_directories(TinyCCompiler PUBLIC ../include)

target_link_libraries(TinyCCompiler tcc)

if(WIN32)
    set(TCC_COMPILE_DEFINITIONS "TCC_TARGET_PE")
endif()
target_compile_definitions(TinyCCompiler PRIVATE "TCC_TARGET_${TCC_TARGET_ARCHITECTURE}" ONE_SOURCE=0 ${TCC_COMPILE_DEFINITIONS})

# copy lib_libtcc1 folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib_libtcc1 DESTINATION ${TCC_RUNTIME_TARGET_DIR})
if(WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/win32/lib_libtcc1 DESTINATION ${TCC_RUNTIME_TARGET_DIR})
endif()

# compile libtcc1-*.a after TinyCCompiler
add_custom_command(TARGET TinyCCompiler POST_BUILD COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/compile_libtcc1 TinyCCompiler WORKING_DIRECTORY ${TCC_RUNTIME_TARGET_DIR})