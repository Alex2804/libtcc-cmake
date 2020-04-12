
if(__detect_arm_features)
    return()
endif()
set(__detect_arm_features INCLUDED)


function(detect_arm_features STATUS_MESSAGE)
    if(${LIBTCC_TARGET_ARCHITECTURE} STREQUAL ARM)
        set(IS_EABI TRUE PARENT_SCOPE)
        set(HAS_VFP TRUE PARENT_SCOPE)
        set(HAS_HARDFLOAT TRUE PARENT_SCOPE)

        if(${STATUS_MESSAGE})
            message(STATUS "Is EABI: ${IS_EABI}")
            message(STATUS "Has VFP: ${HAS_VFP}")
            message(STATUS "Has Hardfloat: ${HAS_HARDFLOAT}")
        endif()
    endif()
endfunction()