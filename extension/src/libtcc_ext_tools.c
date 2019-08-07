char* atcc_concat_path(const char* prefixPath, const char* fileName, const char* fileExtension)
{
    char* path = (char*) tcc_malloc((strlen(prefixPath) + strlen(fileName) + 1 + strlen(fileExtension)) * sizeof(char));
    strcpy(path, prefixPath);
    strcat(path, fileName);
    if(strlen(fileExtension) > 0) {
        strcat(path, ".");
        strcat(path, fileExtension);
    }
    return path;
}

char** atcc_split_string(const char* string, char delimiter)
{
    size_t size;
    char* tmpString;
    char delimiterArray[] = {delimiter};
    int delimiterCount = 0;
    char* token;
    char** splitted;
    size_t i = 0;

    if(string == NULL)
        return NULL;

    size = strlen(string);
    tmpString = (char*) tcc_malloc((size + 1) * sizeof(char));

    strcpy(tmpString, string);

    for(i = 0; i < size; i++) {
        if(string[i] == delimiter) delimiterCount++;
    }

    token = strtok(tmpString, delimiterArray);
    splitted = (char**) tcc_malloc((delimiterCount + 2) * sizeof(char*));

    i = 0;
    while(token != NULL) {
        splitted[i++] = token;
        token = strtok(NULL, delimiterArray);
    }
    splitted[delimiterCount + 1] = NULL;

    return splitted;
}

int atcc_splitted_string_length(char** s)
{
    size_t i;
    for(i = 0; s[i] != NULL; i++);
    return i;
}

void atcc_free_splitted_string(char** splitted)
{
    if(splitted[0] != NULL) {
        tcc_free(splitted[0]);
    }
    tcc_free(splitted);
}

char** atcc_get_libtcc1_files()
{
#ifdef TCC_TARGET_PE
    #ifdef TCC_TARGET_I386
        return split("libtcc1.c;alloca86.S;alloca86-bt.S;chkstk.S;bcheck.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c", ';');
    #elif defined TCC_TARGET_X86_64
        return split("libtcc1.c;alloca86_64.S;alloca86_64-bt.S;chkstk.S;bcheck.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c", ';');
    #elif defined TCC_TARGET_ARM
        return split("libtcc1.c;armeabi.c;alloca-arm.S;armflush.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c", ';');
    #elif defined TCC_TARGET_ARM64
        return split("lib-arm64.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c", ';');
    #endif
#elif defined(TCC_TARGET_MACHO)
    #ifdef TCC_TARGET_I386
        return split("libtcc1.c;alloca86.S;alloca86-bt.S;bcheck.c", ';');
    #elif defined TCC_TARGET_X86_64
        return split("libtcc1.c;alloca86_64.S;alloca86_64-bt.S;va_list.c", ';');
    #elif defined TCC_TARGET_ARM
        return split("libtcc1.c;armeabi.c;alloca-arm.S;armflush.c", ';');
    #elif defined TCC_TARGET_ARM64
        return split("lib-arm64.c", ';', pathPrefix);
    #endif
#else
    #ifdef TCC_TARGET_I386
        return split("libtcc1.c;alloca86.S;alloca86-bt.S;bcheck.c", ';');
    #elif defined TCC_TARGET_X86_64
        return atcc_split_string("libtcc1.c;alloca86_64.S;alloca86_64-bt.S;va_list.c;bcheck.c", ';');
    #elif defined TCC_TARGET_ARM
        return split("libtcc1.c;armeabi.c;alloca-arm.S;armflush.c", ';');
    #elif defined TCC_TARGET_ARM64
        return split("lib-arm64.c", ';');
    #endif
#endif
}

/*
#define TCC_I366_SOURCE_FILES "libtcc1.c;alloca86.S;alloca86-bt.S"
#define TCC_X86_64_SOURCE_FILES "libtcc1.c;alloca86_64.S;alloca86_64-bt.S"
#define TCC_ARM_SOURCE_FILES "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
#define TCC_ARM64_SOURCE_FILES "lib-arm64.c"
#define TCC_WIN_SOURCE_FILES "crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c"

OBJ-i386 = "libtcc1.c;alloca86.S;alloca86-bt.S;bcheck.c"
OBJ-x86_64 = "libtcc1.c;alloca86_64.S;alloca86_64-bt.S;va_list.c;bcheck.c"
OBJ-x86_64-osx = "libtcc1.c;alloca86_64.S;alloca86_64-bt.S;va_list.c"
OBJ-i386-win32 = "libtcc1.c;alloca86.S;alloca86-bt.S;chkstk.S;bcheck.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c"
OBJ-x86_64-win32 = "libtcc1.c;alloca86_64.S;alloca86_64-bt.S;chkstk.S;bcheck.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c"
OBJ-arm64 = "lib-arm64.c"
OBJ-arm = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-fpa = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-fpa-ld = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-vfp = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-eabi = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-eabihf = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c"
OBJ-arm-wince = "libtcc1.c;armeabi.c;alloca-arm.S;armflush.c;crt1.c;crt1w.c;wincrt1.c;wincrt1w.c;dllcrt1.c;dllmain.c"
 */