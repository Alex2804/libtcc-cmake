#if defined(ALIBTCC_ENABLE_EXTENSION) && defined(ALIBTCC1_DESTINATION_PATH)
    if(!alibtcc_extension_is_compiling()) {
        int result;
        FILE *libtcc1_file;
        char* libtcc1_path;
        libtcc1_path = tcc_malloc((strlen(ALIBTCC1_DESTINATION_PATH) + strlen(TCC_LIBTCC1)) * sizeof(char));
        strcpy(libtcc1_path, ALIBTCC1_DESTINATION_PATH);
        strcat(libtcc1_path, TCC_LIBTCC1);
        libtcc1_file = fopen(libtcc1_path, "r");
        tcc_free(libtcc1_path);
        if (!libtcc1_file) {
            result = tcc_build_libtcc1_default();
            if (result) {
                return NULL;
            }
        } else {
            fclose(libtcc1_file);
        }
    }
#endif