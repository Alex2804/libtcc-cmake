cmake_minimum_required(VERSION 2.8.12)

set(LIBTCC_MAJOR_VERSION "0")
set(LIBTCC_MINOR_VERSION "9")
set(LIBTCC_PATCH_VERSION "27")
set(LIBTCC_VERSION "${LIBTCC_MAJOR_VERSION}.${LIBTCC_MINOR_VERSION}.${LIBTCC_PATCH_VERSION}")

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(libtcc C)
    set(PROJECT_VERSION_MAJOR "${LIBTCC_MAJOR_VERSION}")
    set(PROJECT_VERSION_MINOR "${LIBTCC_MINOR_VERSION}")
    set(PROJECT_VERSION_PATCH"${LIBTCC_PATCH_VERSION}")
    set(PROJECT_VERSION "${LIBTCC_VERSION}")
else()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(libtcc VERSION "${LIBTCC_VERSION}" LANGUAGES C)
endif()

include(cmake/libtcc_default_parameter.cmake)

include(cmake/detect_target_architecture.cmake)
include(cmake/detect_arm_features.cmake)
include(cmake/libtcc_compile_definitions.cmake)
include(cmake/libtcc_include_directories.cmake)
include(cmake/libtcc_link_libraries.cmake)
include(cmake/libtcc_sources.cmake)

if(NOT DEFINED LIBTCC_TARGET_SYSTEM)
    string(TOLOWER ${CMAKE_SYSTEM_NAME} LIBTCC_TARGET_SYSTEM)
endif()
if(NOT DEFINED LIBTCC_TARGET_ARCHITECTURE)
    detect_target_architecture(LIBTCC_TARGET_ARCHITECTURE TRUE)
endif()

if(${LIBTCC_TARGET_ARCHITECTURE} STREQUAL I386 OR ${LIBTCC_TARGET_ARCHITECTURE} STREQUAL X86_64 OR
   ${LIBTCC_TARGET_ARCHITECTURE} STREQUAL ARM OR ${LIBTCC_TARGET_ARCHITECTURE} STREQUAL RISCV64)
    string(TOLOWER ${LIBTCC_TARGET_ARCHITECTURE} LIBTCC_SUFFIX)
    detect_arm_features(TRUE)
elseif(${LIBTCC_TARGET_ARCHITECTURE} STREQUAL ARM64)
    set(LIBTCC_SUFFIX aarch64)
else()
    message(FATAL_ERROR "Unknown architecture for libtcc: ${LIBTCC_TARGET_ARCHITECTURE}")
endif()

if(NOT DEFINED LIBTCC_NAME AND LIBTCC_TARGET_SPECIFIC_NAME)
    set(LIBTCC_NAME "libtcc_${LIBTCC_SUFFIX}")
elseif(NOT DEFINED LIBTCC_NAME)
    set(LIBTCC_NAME libtcc)
endif()

string(TOUPPER ${LIBTCC_BUILD_TYPE} LIBTCC_BUILD_TYPE)
if(NOT (LIBTCC_BUILD_TYPE STREQUAL STATIC OR LIBTCC_BUILD_TYPE STREQUAL SHARED))
    message(FATAL_ERROR "Build type ${LIBTCC_BUILD_TYPE} not available!")
endif()

if(LIBTCC_INSTALL_RUNTIME)
    # copy include directories
    if(WIN32 OR APPLE OR ANDROID)
        file(COPY runtime/${LIBTCC_TARGET_SYSTEM}/include DESTINATION ${LIBTCC_RUNTIME_TARGET_PATH})
    else()
        file(COPY runtime/include DESTINATION ${LIBTCC_RUNTIME_TARGET_PATH})
    endif()
endif()

# Generate config.h
message(STATUS "Libtcc generating tcc config.h in \"${LIBTCC_CONFIG_PATH}\" ...")
file(WRITE ${LIBTCC_CONFIG_PATH}/config.h "#define TCC_VERSION \"${LIBTCC_VERSION}\"")

if(LIBTCC_ENABLE_EXTENSION)
    include(extension/cmake/setup_extension.cmake)
endif()

libtcc_sources(LIBTCC_SOURCES TRUE)
libtcc_compile_definitions(LIBTCC_COMPILE_DEFINITIONS TRUE)
libtcc_public_include_directories(LIBTCC_PUBLIC_INCLUDE_DIRECTORIES TRUE)
libtcc_private_include_directories(LIBTCC_PRIVATE_INCLUDE_DIRECTORIES TRUE)
libtcc_link_libraries(LIBTCC_LINK_LIBRARIES TRUE)

add_library(${LIBTCC_NAME} ${LIBTCC_BUILD_TYPE} ${LIBTCC_SOURCES})
set_target_properties(${LIBTCC_NAME} PROPERTIES PREFIX "")
target_include_directories(${LIBTCC_NAME} PUBLIC ${LIBTCC_PUBLIC_INCLUDE_DIRECTORIES}
                                          PRIVATE ${LIBTCC_PRIVATE_INCLUDE_DIRECTORIES})
target_compile_definitions(${LIBTCC_NAME} PUBLIC ${LIBTCC_COMPILE_DEFINITIONS})
target_link_libraries(${LIBTCC_NAME} ${LIBTCC_LINK_LIBRARIES})

if(LIBTCC_TEST)
    add_subdirectory(tests)
endif()
