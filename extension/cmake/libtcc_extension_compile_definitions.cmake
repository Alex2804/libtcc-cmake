
if(__libtcc_extension_compile_definitions)
    return()
endif()
set(__libtcc_extension_compile_definitions INCLUDED)


function(libtcc_extension_compile_definitions FLAG)
    include(extension/cmake/libtcc1_sources.cmake)
    get_libtcc1_sources(LIBTCC1_SOURCES TRUE)
    string(REPLACE ";" ":" LIBTCC1_SOURCES "${LIBTCC1_SOURCES}")
    list(APPEND ${FLAG} ALIBTCC_ENABLE_EXTENSION ALIBTCC1_SOURCES=\"${LIBTCC1_SOURCES}\")

    list(APPEND ${FLAG} ALIBTCC_INCLUDE_PATH=\"${LIBTCC_INCLUDE_PATH}\")

    list(APPEND ${FLAG} ALIBTCC1_SRC_PATH=\"${LIBTCC1_SRC_PATH}\")
    list(APPEND ${FLAG} ALIBTCC1_OBJ_PATH=\"${LIBTCC1_OBJ_PATH}\")
    list(APPEND ${FLAG} ALIBTCC1_DEST_PATH=\"${LIBTCC1_DEST_PATH}\")

    set(${FLAG} "${${FLAG}}" PARENT_SCOPE)
endfunction()