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

include(cmake/DefineDefaultParameter.cmake)

if(NOT DEFINED LIBTCC_TARGET_ARCHITECTURE)
    include(cmake/GetTargetArchitecture.cmake)
    get_target_architecture(LIBTCC_TARGET_ARCHITECTURE TRUE)
endif()

if("${LIBTCC_TARGET_ARCHITECTURE}" STREQUAL "ARM64")
    set(LIBTCC_SUFFIX "aarch64")
elseif("${LIBTCC_TARGET_ARCHITECTURE}" STREQUAL "X86_64" OR "${LIBTCC_TARGET_ARCHITECTURE}" STREQUAL "I386" OR "${LIBTCC_TARGET_ARCHITECTURE}" STREQUAL "ARM")
    string(TOLOWER ${LIBTCC_TARGET_ARCHITECTURE} LOWERCASE_LIBTCC_TARGET_ARCHITECTURE)
    set(LIBTCC_SUFFIX "${LOWERCASE_LIBTCC_TARGET_ARCHITECTURE}")
else()
    message(FATAL_ERROR "Unknown architecture for libtcc: ${LIBTCC_TARGET_ARCHITECTURE}")
endif()

include(cmake/DetectArmFeatures.cmake)
detect_arm_features(LIBTCC_TARGET_ARCHITECTURE HAS_EABI HAS_VFP HAS_HARDFLOAT TRUE)

include(cmake/DefineLibtccDefinitions.cmake)
define_libtcc_definitions(LIBTCC_TARGET_ARCHITECTURE HAS_EABI HAS_VFP HAS_HARDFLOAT LIBTCC_COMPILE_DEFINITIONS TRUE)

if((NOT DEFINED LIBTCC_NAME) AND LIBTCC_TARGET_SPECIFIC_NAME)
    set(LIBTCC_NAME "libtcc_${LIBTCC_SUFFIX}")
elseif(NOT DEFINED LIBTCC_NAME)
    set(LIBTCC_NAME libtcc)
endif()

if(LIBTCC_INSTALL_RUNTIME)
    # copy include directories
    if(WIN32)
        file(COPY "runtime/win32/include" DESTINATION "${LIBTCC_RUNTIME_TARGET_DIR}")
    elseif(APPLE)
        file(COPY "runtime/osx/include" DESTINATION "${LIBTCC_RUNTIME_TARGET_DIR}")
    else()
        file(COPY "runtime/include" DESTINATION "${LIBTCC_RUNTIME_TARGET_DIR}")
    endif()
endif()

# Generate config.h
message(STATUS "Generating tcc config.h in \"${LIBTCC_CONFIG_PATH}\" ...")
file(WRITE ${LIBTCC_CONFIG_PATH} "#define TCC_VERSION \"${LIBTCC_VERSION}\"")
message(STATUS "Generated tcc config.h!")

include(cmake/DefineLibtccSources.cmake)
define_libtcc_sources(LIBTCC_TARGET_ARCHITECTURE LIBTCC_SOURCES TRUE)

if("${LIBTCC_BUILD_TYPE}" STREQUAL "STATIC")
    add_library(${LIBTCC_NAME} STATIC ${LIBTCC_SOURCES})
elseif("${LIBTCC_BUILD_TYPE}" STREQUAL "SHARED")
    add_library(${LIBTCC_NAME} SHARED ${LIBTCC_SOURCES})
else()
    message(FATAL_ERROR "Build type ${LIBTCC_BUILD_TYPE} not available (Build types must be written in uppercase)!")
endif()
set_target_properties(${LIBTCC_NAME} PROPERTIES PREFIX "")

if(${LIBTCC_BUILD_TYPE} MATCHES "SHARED" AND ((NOT DEFINED LIBTCC_INSTALL_SHARED_TO_BINARY AND LIBTCC_INSTALL_SHARED_TO_BINARY_DEFAULT) OR (DEFINED LIBTCC_INSTALL_SHARED_TO_BINARY AND LIBTCC_INSTALL_SHARED_TO_BINARY)))
    set_target_properties(${LIBTCC_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LIBTCC_SHARED_TARGET_DIR})
endif()

target_include_directories(${LIBTCC_NAME} PRIVATE include/tcc src)
target_include_directories(${LIBTCC_NAME} PUBLIC include)

if(LIBTCC_ENABLE_EXTENSION)
    include(extension/cmake/SetupExtension.cmake)
endif()

target_compile_definitions(${LIBTCC_NAME} PUBLIC ${LIBTCC_COMPILE_DEFINITIONS})
if(UNIX)
    target_link_libraries(${LIBTCC_NAME} dl)
    target_compile_options(${LIBTCC_NAME} PRIVATE -Wdeclaration-after-statement -fno-strict-aliasing -Wno-pointer-sign -Wno-sign-compare -Wno-unused-result -Wno-format-truncation)
endif()

if(LIBTCC_TEST)
    add_subdirectory(tests)
endif()
