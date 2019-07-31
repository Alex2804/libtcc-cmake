system(cmake CMakeLists.txt -B qmake_build_tmp -DTCC_RUNTIME_TARGET_DIR=$$OUT_PWD -DTCC_TARGET_ARCHITECTURE=$$TCC_TARGET_ARCHITECTURE)

win32 {
    system(rmdir qmake_build_tmp /s /q)
} else : unix {
    system(rm -rf qmake_build_tmp)
}
