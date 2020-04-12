
if(__libtcc_include_directories)
    return()
endif()
set(__libtcc_include_directories INCLUDED)


function(libtcc_public_include_directories FLAG STATUS_MESSAGE)
    list(APPEND ${FLAG} include)

    if(LIBTCC_ENABLE_EXTENSION)
        include(extension/cmake/libtcc_extension_include_directories.cmake)
        libtcc_extension_public_include_directories(${FLAG})
    endif()

    if(${STATUS_MESSAGE})
        message(STATUS "Libtcc public include directories: ${${FLAG}}")
    endif()

    set(${FLAG} ${${FLAG}} PARENT_SCOPE)
endfunction()


function(libtcc_private_include_directories FLAG STATUS_MESSAGE)
    list(APPEND ${FLAG} include/tcc ${LIBTCC_CONFIG_PATH})

    if(${STATUS_MESSAGE})
        message(STATUS "Libtcc private include directories: ${${FLAG}}")
    endif()

    set(${FLAG} ${${FLAG}} PARENT_SCOPE)
endfunction()
