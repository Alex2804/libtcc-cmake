
if(__libtcc_extension_sources)
    return()
endif()
set(__libtcc_extension_sources INCLUDED)

function(libtcc_extension_sources FLAG)
    if(NOT LIBTCC_ONE_SOURCE)
        list(APPEND ${FLAG} src/tcctools.c extension/src/libtcc_ext.c extension/src/private/src/utility.c extension/src/private/src/filesystem.c extension/src/private/src/str_builder.c)
    endif()
    set(${FLAG} ${${FLAG}} PARENT_SCOPE)
endfunction()