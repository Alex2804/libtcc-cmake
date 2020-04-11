
if(__libtcc_extension_sources)
    return()
endif()
set(__libtcc_extension_sources INCLUDED)

function(libtcc_extension_sources __LIBTCC_SOURCES__)
    if(DEFINED ${__LIBTCC_SOURCES__})
        list(APPEND __SOURCES__ "${${__LIBTCC_SOURCES__}}")
    endif()

    list(APPEND __SOURCES__ extension/src/libtcc_ext.c extension/src/private/src/utility.c extension/src/private/src/filesystem.c extension/src/private/src/str_builder.c)
    if(NOT LIBTCC_ONE_SOURCE)
        list(APPEND __SOURCES__ src/tcctools.c)
    endif()

    set(${__LIBTCC_SOURCES__} ${__SOURCES__} PARENT_SCOPE)
endfunction()