cmake_minimum_required(VERSION 3.14)
project(libtcc C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(cmake/DefineDefaultParameter.cmake)

if(NOT DEFINED TCC_TARGET_ARCHITECTURE)
    include(cmake/GetTargetArchitecture.cmake)
    get_target_architecture(TCC_TARGET_ARCHITECTURE TRUE)
endif()

if(TCC_TARGET_ARCHITECTURE STREQUAL "X86_64") # 64 bit
    set(LIBTCC_POSTFIX "64")
elseif(TCC_TARGET_ARCHITECTURE STREQUAL "I386") # 32 bit
    set(LIBTCC_POSTFIX "32")
elseif(TCC_TARGET_ARCHITECTURE STREQUAL "ARM") # arm
    set(LIBTCC_POSTFIX "arm")
else()
    message(FATAL_ERROR "Unknown Architecture for TCC Library: ${TCC_TARGET_ARCHITECTURE}")
endif()

if((NOT DEFINED LIBTCC_NAME) AND TCC_TARGET_SPECIFIC_NAME)
    set(LIBTCC_NAME "tcc_${LIBTCC_POSTFIX}")
elseif(NOT DEFINED LIBTCC_NAME)
    set(LIBTCC_NAME tcc)
endif()

if(WIN32)
    list(APPEND LIBTCC_COMPILE_DEFINITIONS "TCC_TARGET_PE")
elseif(UNIX)
    list(APPEND LIBTCC_COMPILE_DEFINITIONS "CONFIG_TRIPLET=x86_64-linux-gnu")
    list(APPEND LIBTCC_COMPILE_OPTIONS "-Wdeclaration-after-statement -fno-strict-aliasing -Wno-pointer-sign -Wno-sign-compare -Wno-unused-result -Wno-format-truncation")
endif()

if(TCC_INSTALL_RUNTIME)
    # copy include directories
    file(COPY "runtime/include" DESTINATION "${TCC_RUNTIME_TARGET_DIR}")
    if(WIN32)
        file(COPY "runtime/win32/include" DESTINATION "${TCC_RUNTIME_TARGET_DIR}")
    endif()
    # compile libtcc1-*.a
    add_subdirectory(tcc)
endif()

# Generate config.h
message("generating tcc config.h in \"${TCC_CONFIG_PATH}\" ...")
file(WRITE ${TCC_CONFIG_PATH} "#define TCC_VERSION \"${TCC_VERSION}\"")
message("generated tcc config.h!")

include_directories(include/tcc src)

if(${TCC_BUILD_TYPE} STREQUAL "STATIC")
    add_library(${LIBTCC_NAME} STATIC src/libtcc.c)
elseif(${TCC_BUILD_TYPE} STREQUAL "SHARED")
    if(WIN32)
        list(APPEND LIBTCC_COMPILE_DEFINITIONS "LIBTCC_AS_DLL")
    endif()
    add_library(${LIBTCC_NAME} SHARED src/libtcc.c)
else()
    message(FATAL_ERROR "build type ${TCC_BUILD_TYPE} not available (Build types must be written in uppercase)!")
endif()

target_include_directories(${LIBTCC_NAME} PRIVATE include/tcc src)
target_include_directories(${LIBTCC_NAME} PUBLIC include)

if(UNIX)
    target_link_libraries(${LIBTCC_NAME} dl)
endif()

target_compile_definitions(${LIBTCC_NAME} PRIVATE "TCC_TARGET_${TCC_TARGET_ARCHITECTURE}" ONE_SOURCE=1 TCC_LIBTCC1="libtcc1-${LIBTCC_POSTFIX}.a" ${LIBTCC_COMPILE_DEFINITIONS})
target_compile_options(${LIBTCC_NAME} PRIVATE ${LIBTCC_COMPILE_OPTIONS})

if(LIBTCC_TEST)
    add_subdirectory(tests)
endif()