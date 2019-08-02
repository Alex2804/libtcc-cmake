set(TCC_VERSION 0.9.27)
set(TCC_CONFIG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/tcc/config.h")

set(TCC_RUNTIME_TARGET_DIR_DEFAULT ${CMAKE_BINARY_DIR})
set(TCC_SHARED_TARGET_DIR_DEFAULT ${CMAKE_BINARY_DIR})
set(TCC_BUILD_TYPE_DEFAULT STATIC)
set(TCC_TARGET_SPECIFIC_NAME_DEFAULT FALSE)
set(TCC_INSTALL_RUNTIME_DEFAULT TRUE)
set(TCC_INSTALL_SHARED_TO_BINARY_DEFAULT TRUE)

if(NOT DEFINED TCC_RUNTIME_TARGET_DIR)
    set(TCC_RUNTIME_TARGET_DIR ${TCC_RUNTIME_TARGET_DIR_DEFAULT})
endif()
if(NOT DEFINED TCC_SHARED_TARGET_DIR)
    set(TCC_SHARED_TARGET_DIR ${TCC_SHARED_TARGET_DIR_DEFAULT})
endif()
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
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TCC_SHARED_TARGET_DIR})
endif()