
if(__libtcc_extension_include_directories)
    return()
endif()
set(__libtcc_extension_include_directories INCLUDED)


function(libtcc_extension_public_include_directories FLAG)
    list(APPEND ${FLAG} extension/include)
    set(${FLAG} ${${FLAG}} PARENT_SCOPE)
endfunction()
