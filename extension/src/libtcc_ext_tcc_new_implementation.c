// This contains the extension implementation which is required in tcc_new()
# include "libtcc_ext_private.h"

if (!alibtcc_extension_is_compiling()) {
    int result;
    FILE *libtcc1_file;
    char *libtcc1_path;
    size_t path_length = strlen(ALIBTCC1_DEST_PATH);
    size_t name_length = strlen(TCC_LIBTCC1);
    libtcc1_path = (char *) tcc_malloc((path_length + name_length + 1) * sizeof(char));
    strcpy(libtcc1_path, ALIBTCC1_DEST_PATH);
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