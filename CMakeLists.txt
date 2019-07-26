cmake_minimum_required(VERSION 3.14)
project(libtcc C)

set(CMAKE_C_STANDARD 99)

set(TCC_VERSION 0.9.27)
set(TCC_BUILD_TYPE_DEFAULT STATIC)
set(TCC_TARGET_SPECIFIC_NAME_DEFAULT FALSE)
set(TCC_INSTALL_RUNTIME_DEFAULT TRUE)
set(TCC_INSTALL_SHARED_TO_BINARY_DEFAULT TRUE)

if(NOT DEFINED TCC_BUILD_TYPE)
    set(TCC_BUILD_TYPE ${TCC_BUILD_TYPE_DEFAULT})
endif()
if(NOT DEFINED TCC_TARGET_SPECIFIC_NAME)
    set(TCC_TARGET_SPECIFIC_NAME ${TCC_TARGET_SPECIFIC_NAME_DEFAULT})
endif()
if(NOT DEFINED TCC_INSTALL_RUNTIME)
    set(TCC_INSTALL_RUNTIME ${TCC_INSTALL_RUNTIME_DEFAULT})
endif()
if(${TCC_BUILD_TYPE} MATCHES "SHARED" AND ((NOT DEFINED TCC_INSTALL_SHARED_TO_BINARY AND TCC_INSTALL_SHARED_TO_BINARY_DEFAULT) OR (DEFINED TCC_INSTALL_SHARED_TO_BINARY AND TCC_INSTALL_SHARED_TO_BINARY)))
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()


if(NOT DEFINED TARGET_ARCHITECTURE)
    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    include(GetTargetArchitecture)
    get_target_architecture(TARGET_ARCHITECTURE TRUE)
endif()

if(TARGET_ARCHITECTURE STREQUAL "X86_64") # 64 bit
    set(TCC_LIB_PREFIX "64")
    add_compile_definitions(TCC_LIBTCC1="libtcc1-64.a")
elseif(TARGET_ARCHITECTURE STREQUAL "I386") # 32 bit
    set(TCC_LIB_PREFIX "32")
    add_compile_definitions(TCC_LIBTCC1="libtcc1-32.a")
elseif(TARGET_ARCHITECTURE STREQUAL "ARM") # arm
    set(TCC_LIB_PREFIX "arm")
else()
    message(FATAL_ERROR "Unknown Architecture for TCC Library: ${TARGET_ARCHITECTURE}")
endif()

if(TCC_TARGET_SPECIFIC_NAME)
    set(TCC_LIB_NAME "tcc_${TCC_LIB_PREFIX}")
else()
    set(TCC_LIB_NAME tcc)
endif()

add_compile_definitions("TCC_TARGET_${TARGET_ARCHITECTURE}" ONE_SOURCE=1)
if(WIN32)
    add_compile_definitions(TCC_TARGET_PE)
elseif(UNIX)
    add_compile_definitions(CONFIG_TRIPLET="x86_64-linux-gnu")
    add_compile_options(-Wdeclaration-after-statement -fno-strict-aliasing -Wno-pointer-sign -Wno-sign-compare -Wno-unused-result -Wno-format-truncation)
endif()

if(TCC_INSTALL_RUNTIME)
    add_subdirectory(runtime)
endif()

# Generate config.h
set(TCC_CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/tcc/config.h")
message("generating tcc config.h in \"${TCC_CONFIG_DIR}\" ...")
file(WRITE ${TCC_CONFIG_DIR} "#define TCC_VERSION \"${TCC_VERSION}\"")
message("generated tcc config.h!")

include_directories(include/tcc src)

if(${TCC_BUILD_TYPE} STREQUAL "STATIC")
    add_library(${TCC_LIB_NAME} STATIC src/libtcc.c)
elseif(${TCC_BUILD_TYPE} STREQUAL "SHARED")
    if(WIN32)
        add_compile_definitions(LIBTCC_AS_DLL)
    endif()
    add_library(${TCC_LIB_NAME} SHARED src/libtcc.c)
else()
    message(FATAL_ERROR "build type ${TCC_BUILD_TYPE} not available (Build types must be uppercase)!")
endif()

target_include_directories(${TCC_LIB_NAME} PRIVATE include/tcc src)
target_include_directories(${TCC_LIB_NAME} PUBLIC include)

if(UNIX)
    target_link_libraries(${TCC_LIB_NAME} dl)
endif()