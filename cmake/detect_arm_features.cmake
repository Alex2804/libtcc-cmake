
if(__detect_arm_features)
    return()
endif()
set(__detect_arm_features INCLUDED)

function(detect_arm_features __STATUS_MESSAGE__)
    set(IS_EABI TRUE PARENT_SCOPE)
    set(HAS_VFP TRUE PARENT_SCOPE)
    set(HAS_HARDFLOAT TRUE PARENT_SCOPE)

    if(${__STATUS_MESSAGE__})
        message(STATUS "Is EABI: ${IS_EABI}")
        message(STATUS "Has VFP: ${HAS_VFP}")
        message(STATUS "Has Hardfloat: ${HAS_HARDFLOAT}")
    endif()
endfunction()