TARGET = tcc

TEMPLATE = lib
CONFIG += C99

TCC_VERSION = 0.9.27
TCC_CONFIG_PATH = "$${_PRO_FILE_PWD_}/include/tcc/config.h"
TCC_BUILD_TYPE_DEFAULT = SHARED
TCC_TARGET_SPECIFIC_NAME_DEFAULT = False
TCC_INSTALL_RUNTIME_DEFAULT = True
TCC_INSTALL_SHARED_TO_BINARY_DEFAULT = True

isEmpty(TCC_BUILD_TYPE) {
    TCC_BUILD_TYPE = $${TCC_BUILD_TYPE_DEFAULT}
}
isEmpty(TCC_TARGET_SPECIFIC_NAME) {
    TCC_TARGET_SPECIFIC_NAME = $${TCC_TARGET_SPECIFIC_NAME_DEFAULT}
}
isEmpty(TCC_INSTALL_RUNTIME) {
    TCC_INSTALL_RUNTIME = $${TCC_INSTALL_RUNTIME_DEFAULT}
}
isEmpty(TCC_INSTALL_SHARED_TO_BINARY) {
    TCC_INSTALL_SHARED_TO_BINARY = $${TCC_INSTALL_SHARED_TO_BINARY_DEFAULT}
}
isEqual(TCC_BUILD_TYPE, SHARED) : isEqual(TCC_INSTALL_SHARED_TO_BINARY, True) {

}

isEmpty(TCC_TARGET_ARCHITECTURE) {
    isEqual(QT_ARCH, x86_64) {
        TCC_TARGET_ARCHITECTURE = X86_64
    } else : isEqual(QT_ARCH.arch, x86) {
        TCC_TARGET_ARCHITECTURE = I386
    }
    message("Target Architecture: $${TCC_TARGET_ARCHITECTURE}")
}

isEqual(TCC_TARGET_ARCHITECTURE, X86_64) {
    TCC_LIB_POSTFIX = 64
} else : isEqual(TCC_TARGET_ARCHITECTURE, I386) {
    TCC_LIB_POSTFIX = 32
} else : isEqual(TCC_TARGET_ARCHITECTURE, ARM) {
    TCC_LIB_POSTFIX = arm
} else {
    error("Unknown Architecture for TCC Library: $${TCC_TARGET_ARCHITECTURE}")
}

isEmpty(TCC_LIB_NAME) : isEqual(TCC_TARGET_SPECIFIC_NAME, True) {
    TCC_LIB_NAME = "tcc_$${TCC_LIB_POSTFIX}"
} else : isEmpty(TCC_LIB_NAME) {
    TCC_LIB_NAME = "tcc"
}

DEFINES += "TCC_TARGET_$${TCC_TARGET_ARCHITECTURE}" ONE_SOURCE=1 TCC_LIBTCC1=\\\"libtcc1-32.a\\\"
win32 {
    DEFINES += TCC_TARGET_PE
} else : unix {
    DEFINES += CONFIG_TRIPLET=\\\"x86_64-linux-gnu\\\"
    CONFIG += -Wdeclaration-after-statement -fno-strict-aliasing -Wno-pointer-sign -Wno-sign-compare -Wno-unused-result -Wno-format-truncation
}

isEqual(TCC_INSTALL_RUNTIME, True) {
    include($$PWD/runtime/runtime.pri)
}

message("generating tcc config.h in \"$${TCC_CONFIG_PATH}\" ...")
__TCC_CONFIG_CONTENT__ = "$${LITERAL_HASH}define TCC_VERSION \"$${TCC_VERSION}\""
!write_file($${TCC_CONFIG_PATH}, __TCC_CONFIG_CONTENT__) {
    error("Couldn't Generate $${TCC_CONFIG_PATH}")
}
message("generated tcc config.h!")

INCLUDEPATH += $$PWD/include/tcc $$PWD/src

SOURCES += src/libtcc.c
isEqual(TCC_BUILD_TYPE, STATIC) {
    CONFIG += static
} else : isEqual(TCC_BUILD_TYPE, SHARED) {
    win32 {
        DEFINES += LIBTCC_AS_DLL
    }
    CONFIG += shared
} else {
    error("build type $${TCC_BUILD_TYPE} not available (Build types must be written in uppercase)!")
}

unix {
    LIBS += -ldl
}

android {
    QMAKE_LFLAGS += -nostdlib++
}
