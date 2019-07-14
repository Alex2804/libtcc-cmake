cmake_minimum_required(VERSION 3.14)
project(tcc C)

set(CMAKE_C_STANDARD 99)

set(TCC_VERSION 0.9.27)
set(TCC_STATIC_BUILD_DEFAULT TRUE)
set(TCC_TARGET_SPECIFIC_NAME_DEFAULT FALSE)
set(TCC_INSTALL_RUNTIME_DEFAULT TRUE)
set(TCC_INSTALL_SHARED_TO_BINARY_DEFAULT TRUE)

if(NOT DEFINED TCC_STATIC_BUILD)
    set(TCC_STATIC_BUILD ${TCC_STATIC_BUILD_DEFAULT})
endif()
if(NOT DEFINED TCC_TARGET_SPECIFIC_NAME)
    set(TCC_TARGET_SPECIFIC_NAME ${TCC_TARGET_SPECIFIC_NAME_DEFAULT})
endif()
if(NOT DEFINED TCC_INSTALL_RUNTIME)
    set(TCC_INSTALL_RUNTIME ${TCC_INSTALL_RUNTIME_DEFAULT})
endif()
if(NOT TCC_STATIC_BUILD AND ((NOT DEFINED TCC_INSTALL_SHARED_TO_BINARY AND TCC_INSTALL_SHARED_TO_BINARY_DEFAULT) OR (DEFINED TCC_INSTALL_SHARED_TO_BINARY AND TCC_INSTALL_SHARED_TO_BINARY)))
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()


if(NOT DEFINED TARGET_ARCHITECTURE)
    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    include(GetTargetArchitecture)
    get_target_architecture(TARGET_ARCHITECTURE TRUE)
endif()

if(TARGET_ARCHITECTURE STREQUAL "X86_64") # 64 bit
    set(TCC_LIB_PREFIX "64")
elseif(TARGET_ARCHITECTURE STREQUAL "I386") # 32 bit
    set(TCC_LIB_PREFIX "32")
elseif(TARGET_ARCHITECTURE STREQUAL "ARM") # arm
    set(TCC_LIB_PREFIX "arm")
else()
    message("Unknown Architecture for TCC Library: ${TARGET_ARCHITECTURE}")
endif()

if(TCC_TARGET_SPECIFIC_NAME)
    set(TCC_LIB_NAME "tcc_${TCC_LIB_PREFIX}")
else()
    set(TCC_LIB_NAME tcc)
endif()

add_compile_definitions(ONE_SOURCE=1 "TCC_TARGET_${TARGET_ARCHITECTURE}")

if(WIN32)
    add_compile_definitions(TCC_TARGET_PE)
    add_subdirectory(win32)
endif()

if(TCC_INSTALL_RUNTIME)
    add_subdirectory(runtime)
endif()

include_directories(include/tcc src)

if(TCC_STATIC_BUILD)
    add_library(${TCC_LIB_NAME} STATIC src/libtcc.c)
    message(static)
else()
    message(shared)
    if(WIN32)
        add_compile_definitions(LIBTCC_AS_DLL)
    endif()
    add_library(${TCC_LIB_NAME} SHARED src/libtcc.c)
endif()