
if(__get_libtcc1_sources)
    return()
endif()
set(__get_libtcc1_sources INCLUDED)


function(get_libtcc1_sources FLAG STATUS_MESSAGE)
    set(SOURCES_BCHECK bcheck.c)
    set(SOURCES_BT bt-log.c)
    set(SOURCES_B bcheck.c bt-dll.c)

    set(SOURCES_DSO dsohandle.c)

    set(SOURCES_WIN crt1.c crt1w.c wincrt1.c wincrt1w.c dllcrt1.c dllmain.c)

    set(SOURCES_I386 libtcc1.c alloca86.S alloca86-bt.S ${SOURCES_BT})
    set(SOURCES_X86_64 libtcc1.c alloca86_64.S alloca86_64-bt.S ${SOURCES_BT})
    set(SOURCES_ARM libtcc1.c armeabi.c alloca-arm.S armflush.c ${SOURCES_BT})
    set(SOURCES_ARM64 lib-arm64.c ${SOURCES_BT})
    set(SOURCES_RISCV64 lib-arm64.c ${SOURCES_BT})

    list(APPEND ${FLAG} ${SOURCES_${LIBTCC_TARGET_ARCHITECTURE}})
    if(LIBTCC_TARGET_SYSTEM STREQUAL "windows")
        list(APPEND ${FLAG} ${SOURCES_WIN})
        if(LIBTCC_TARGET_ARCHITECTURE STREQUAL "I386" OR LIBTCC_TARGET_ARCHITECTURE STREQUAL "X86_64")
            list(APPEND ${FLAG} chkstk.S ${SOURCES_B})
        endif()
    elseif(LIBTCC_TARGET_SYSTEM STREQUAL "darwin")
        if(LIBTCC_TARGET_ARCHITECTURE STREQUAL "X86_64")
            list(APPEND ${FLAG} va_list.c)
        endif()
    else()
        if(LIBTCC_TARGET_ARCHITECTURE STREQUAL "X86_64")
            list(APPEND ${FLAG} va_list.c)
        endif()
        if((LIBTCC_TARGET_ARCHITECTURE STREQUAL "I386" OR LIBTCC_TARGET_ARCHITECTURE STREQUAL "X86_64") AND NOT ANDROID)
            list(APPEND ${FLAG} ${SOURCES_BCHECK})
        endif()
        list(APPEND ${FLAG} ${SOURCES_DSO})
    endif()

    if(${STATUS_MESSAGE})
        message(STATUS "Libtcc1 source files: ${${FLAG}}")
    endif()

    set(${FLAG} ${${FLAG}} PARENT_SCOPE)
endfunction()