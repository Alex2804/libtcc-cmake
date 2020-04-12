
if(__libtcc_compile_definitions)
    return()
endif()
set(__libtcc_compile_definitions INCLUDED)


function(libtcc_compile_definitions FLAG STATUS_MESSAGE)
    if(NOT DEFINED LIBTCC1_NAME)
        set(LIBTCC1_NAME "libtcc1-${LIBTCC_SUFFIX}.a")
    endif()
    list(APPEND ${FLAG} TCC_LIBTCC1="${LIBTCC1_NAME}")
    list(APPEND ${FLAG} TCC_TARGET_${LIBTCC_TARGET_ARCHITECTURE})

    if(LIBTCC_ONE_SOURCE)
        list(APPEND ${FLAG} ONE_SOURCE=1)
    else()
        list(APPEND ${FLAG} ONE_SOURCE=0)
    endif()

    if(WIN32)
        list(APPEND ${FLAG} TCC_TARGET_PE)
        if(LIBTCC_BUILD_TYPE STREQUAL "SHARED")
            list(APPEND ${FLAG} LIBTCC_AS_DLL)
        endif()
    elseif(APPLE)
        if(NOT ${LIBTCC_TARGET_ARCHITECTURE} STREQUAL X86_64)
            message(FATAL_ERROR "Libtcc only supports x86_64 on macOS!")
        endif()
        list(APPEND ${FLAG} TCC_TARGET_MACHO _ANSI_SOURCE)
    elseif(LIBTCC_TARGET_SYSTEM STREQUAL "linux")
        if(IS_EABI)
            if(HAS_HARDFLOAT)
                set(LIBTCC_CONFIG_TRIPLET_ABI gnueabihf)
            else()
                set(LIBTCC_CONFIG_TRIPLET_ABI gnueabi)
            endif()
        else()
            set(LIBTCC_CONFIG_TRIPLET_ABI gnu)
        endif()
        list(APPEND ${FLAG} CONFIG_TRIPLET=\"${LIBTCC_SUFFIX}-${LIBTCC_TARGET_SYSTEM}-${LIBTCC_CONFIG_TRIPLET_ABI}\")
    endif()

    if(IS_EABI)
        list(APPEND ${FLAG} TCC_ARM_EABI)
    endif()
    if(HAS_VFP)
        list(APPEND ${FLAG} TCC_ARM_VFP)
    endif()
    if(HAS_HARDFLOAT)
        list(APPEND ${FLAG} TCC_ARM_HARDFLOAT)
    endif()

    if(LIBTCC_ENABLE_EXTENSION)
        include(extension/cmake/libtcc_extension_compile_definitions.cmake)
        libtcc_extension_compile_definitions(${FLAG})
    endif()

    if(STATUS_MESSAGE)
        message(STATUS "Libtcc compile definitions: ${${FLAG}}")
    endif()

    set(${FLAG} ${${FLAG}} PARENT_SCOPE)
endfunction()