
if(__libtcc_link_libraries)
    return()
endif()
set(__libtcc_link_libraries INCLUDED)


function(libtcc_link_libraries FLAG STATUS_MESSAGE)
    if(UNIX)
        list(APPEND ${FLAG} "dl")
    endif()
    if(ANDROID)
        find_library(android-lib android)
        list(APPEND ${FLAG} "${android-lib}")
    endif()

    if(STATUS_MESSAGE)
        message(STATUS "Libtcc link libraries: ${${FLAG}}")
    endif()

    set(${FLAG} ${${FLAG}} PARENT_SCOPE)
endfunction()