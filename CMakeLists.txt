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

include(cmake/default_parameter.cmake)

if(NOT DEFINED LIBTCC_TARGET_ARCHITECTURE)
    include(cmake/detect_target_architecture.cmake)
    detect_target_architecture(LIBTCC_TARGET_ARCHITECTURE TRUE)
endif()
string(TOLOWER ${LIBTCC_TARGET_ARCHITECTURE} LOWERCASE_LIBTCC_TARGET_ARCHITECTURE)

if(${LIBTCC_TARGET_ARCHITECTURE} STREQUAL ARM64)
    set(LIBTCC_SUFFIX "aarch64")
elseif(${LIBTCC_TARGET_ARCHITECTURE} STREQUAL X86_64 OR ${LIBTCC_TARGET_ARCHITECTURE} STREQUAL I386 OR ${LIBTCC_TARGET_ARCHITECTURE} STREQUAL ARM)
    set(LIBTCC_SUFFIX "${LOWERCASE_LIBTCC_TARGET_ARCHITECTURE}")
else()
    message(FATAL_ERROR "Unknown architecture for libtcc: ${LIBTCC_TARGET_ARCHITECTURE}")
endif()

include(cmake/detect_arm_features.cmake)
detect_arm_features(LIBTCC_TARGET_ARCHITECTURE HAS_EABI HAS_VFP HAS_HARDFLOAT TRUE)

include(cmake/libtcc_compile_definitions.cmake)
define_libtcc_definitions(LIBTCC_TARGET_ARCHITECTURE HAS_EABI HAS_VFP HAS_HARDFLOAT LIBTCC_COMPILE_DEFINITIONS TRUE)

if(NOT DEFINED LIBTCC_NAME AND LIBTCC_TARGET_SPECIFIC_NAME)
    set(LIBTCC_NAME "libtcc_${LIBTCC_SUFFIX}")
elseif(NOT DEFINED LIBTCC_NAME)
    set(LIBTCC_NAME libtcc)
endif()

if(LIBTCC_INSTALL_RUNTIME)
    # copy include directories
    if(WIN32 OR APPLE)
        string(TOLOWER ${CMAKE_SYSTEM_NAME} RUNTIME_SYSTEM_DIR)
    else()
        set(RUNTIME_SYSTEM_DIR ".")
    endif()
    file(COPY runtime/${RUNTIME_SYSTEM_DIR}/include DESTINATION ${CMAKE_BINARY_DIR})
endif()

# Generate config.h
message(STATUS "Generating tcc config.h in \"${LIBTCC_CONFIG_PATH}\" ...")
file(WRITE ${LIBTCC_CONFIG_PATH} "#define TCC_VERSION \"${LIBTCC_VERSION}\"")
message(STATUS "Generated tcc config.h!")

include(cmake/libtcc_sources.cmake)
define_libtcc_sources(LIBTCC_TARGET_ARCHITECTURE LIBTCC_SOURCES TRUE)

string(TOUPPER ${LIBTCC_BUILD_TYPE} LIBTCC_BUILD_TYPE)
if(${LIBTCC_BUILD_TYPE} STREQUAL STATIC)
    add_library(${LIBTCC_NAME} STATIC ${LIBTCC_SOURCES})
elseif(${LIBTCC_BUILD_TYPE} STREQUAL SHARED)
    add_library(${LIBTCC_NAME} SHARED ${LIBTCC_SOURCES})
else()
    message(FATAL_ERROR "Build type ${LIBTCC_BUILD_TYPE} not available!")
endif()
set_target_properties(${LIBTCC_NAME} PROPERTIES PREFIX "")

target_include_directories(${LIBTCC_NAME} PRIVATE include/tcc src)
target_include_directories(${LIBTCC_NAME} PUBLIC include)

if(LIBTCC_ENABLE_EXTENSION)
    include(extension/cmake/setup_extension.cmake)
endif()

target_compile_definitions(${LIBTCC_NAME} PUBLIC ${LIBTCC_COMPILE_DEFINITIONS})

include(cmake/libtcc_link_libraries.cmake)
define_libtcc_link_libraries(LIBTCC_LINK_LIBRARIES TRUE)
target_link_libraries(${LIBTCC_NAME} ${LIBTCC_LINK_LIBRARIES})

if(LIBTCC_TEST)
    add_subdirectory(tests)
endif()
