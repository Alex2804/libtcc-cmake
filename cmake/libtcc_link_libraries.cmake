
if(__define_libtcc_link_libraries)
    return()
endif()
set(__define_libtcc_link_libraries INCLUDED)

function(define_libtcc_link_libraries __LIBTCC_LINK_LIBRARIES__ __STATUS_MESSAGE__)
    if(DEFINED ${__LIBTCC_LINK_LIBRARIES__})
        list(APPEND __LINK_LIBRARIES__ "${${__LIBTCC_LINK_LIBRARIES__}}")
    endif()

    if(UNIX)
        list(APPEND __LINK_LIBRARIES__ "dl")
    endif()
    if(ANDROID)
        find_library(android-lib android)
        list(APPEND __LINK_LIBRARIES__ "${android-lib}")
    endif()

    if(${__STATUS_MESSAGE__})
        message(STATUS "Libtcc link libraries: ${__LINK_LIBRARIES__}")
    endif()

    set(${__LIBTCC_LINK_LIBRARIES__} ${__LINK_LIBRARIES__} PARENT_SCOPE)
endfunction()