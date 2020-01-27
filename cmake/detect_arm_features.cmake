
if(__detect_arm_features)
    return()
endif()
set(__detect_arm_features INCLUDED)

function(detect_arm_features __TARGET_ARCHITECTURE__ __HAS_EABI__ __HAS_VFP__ __HAS_HARDFLOAT__ __STATUS_MESSAGE__)
    if(${${__TARGET_ARCHITECTURE__}} STREQUAL ARM)
        set(__ARCHITECTURE_HAS_EABI__ TRUE)
        set(__ARCHITECTURE_HAS_VFP__ TRUE)
        set(__ARCHITECTURE_HAS_HARDFLOAT__ TRUE)

        # EABI
        if(NOT DEFINED ${__HAS_EABI__})
            set(${__HAS_EABI__} "${__ARCHITECTURE_HAS_EABI__}" PARENT_SCOPE)
        else()
            set(__ARCHITECTURE_HAS_EABI__ ${${__HAS_EABI__}})
        endif()

        # VFP
        if(NOT DEFINED ${__HAS_VFP__})
            set(${__HAS_VFP__} "${__ARCHITECTURE_HAS_VFP__}" PARENT_SCOPE)
        else()
            set(__ARCHITECTURE_HAS_VFP__ ${${__HAS_VFP__}})
        endif()

        # Hardfloat
        if(NOT DEFINED ${__HAS_HARDFLOAT__})
            set(${__HAS_HARDFLOAT__} "${__ARCHITECTURE_HAS_HARDFLOAT__}" PARENT_SCOPE)
        else()
            set(__ARCHITECTURE_HAS_HARDFLOAT__ ${${__HAS_HARDFLOAT__}})
        endif()

        if(${__STATUS_MESSAGE__})
            message(STATUS "has Eabi: ${__ARCHITECTURE_HAS_EABI__}")
            message(STATUS "has VFP: ${__ARCHITECTURE_HAS_VFP__}")
            message(STATUS "has Hardfloat: ${__ARCHITECTURE_HAS_HARDFLOAT__}")
        endif()
    endif()
endfunction()