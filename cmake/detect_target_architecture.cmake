
if(__detect_target_architecture)
    return()
endif()
set(__detect_target_architecture INCLUDED)


function(detect_target_architecture FLAG STATUS_MESSAGE)
    if(CMAKE_CL_64)
        set(MSVC64 1)
    endif()

    if(NOT DEFINED CV_GCC AND CMAKE_C_COMPILER_ID MATCHES "GNU")
        set(CV_GCC 1)
    endif()

    if(NOT DEFINED CMAKE_C_COMPILER_VERSION)
        message(WARNING "Compiler version is not available: CMAKE_C_COMPILER_VERSION is not set")
    endif()

    if(WIN32 AND CV_GCC)
        execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpmachine
                OUTPUT_VARIABLE OPENCV_GCC_TARGET_MACHINE
                OUTPUT_STRIP_TRAILING_WHITESPACE)
        if(OPENCV_GCC_TARGET_MACHINE MATCHES "amd64|x86_64|AMD64")
            set(MINGW64 1)
        endif()
    endif()

    if(MSVC64 OR MINGW64)
        set(X86_64 1)
    elseif(MINGW OR (MSVC AND NOT CMAKE_CROSSCOMPILING))
        set(X86 1)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64.*|x86_64.*|AMD64.*")
        set(X86_64 1)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i686.*|i386.*|x86.*|amd64.*|AMD64.*")
        set(X86 1)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm.*|ARM.*)")
        set(ARM 1)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64.*|AARCH64.*)")
        set(AARCH64 1)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(powerpc|ppc)64le")
        set(PPC64LE 1)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(powerpc|ppc)64")
        set(PPC64 1)
    endif()

    # Workaround for 32-bit operating systems on 64-bit x86_64 processor
    if(X86_64 AND CMAKE_SIZEOF_VOID_P EQUAL 4 AND NOT FORCE_X86_64)
        message(STATUS "sizeof(void) = 4 on x86 / x86_64 processor. Assume 32-bit compilation mode (X86=1)")
        unset(X86_64)
        set(X86 1)
    endif()

    if(X86_64)
        set(ARCH "X86_64")
    elseif(X86)
        set(ARCH "I386")
    elseif(ARM)
        set(ARCH "ARM")
    elseif(AARCH64)
        set(ARCH "ARM64")
    elseif(PPC64LE)
        set(ARCH "ppc64le")
    elseif(PPC64)
        set(ARCH "ppc64")
    endif()

    if(STATUS_MESSAGE)
        message(STATUS "Target Architecture: ${ARCH}")
    endif()
    set(${FLAG} "${ARCH}" PARENT_SCOPE)

endfunction()