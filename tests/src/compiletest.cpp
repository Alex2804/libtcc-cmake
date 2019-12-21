#include "gtest/gtest.h"

#include "tcc/libtcc_ext.h"

#include <fstream>

int deleteLibtcc1()
{
    std::FILE *libtcc1_file;
    std::string path = std::string(ALIBTCC1_DEST_PATH) + TCC_LIBTCC1;
    libtcc1_file = std::fopen(path.c_str(), "r");
    if (libtcc1_file) {
        std::fclose(libtcc1_file);
        return remove(path.c_str());
    }
    return false;
}

GTEST_TEST(Libtcc_Extension_Compile__Tests, Compile_1) {
    const char* string = "#include<math.h>\n"
                         "int test() {\n"
                         "  return pow(4, 4);\n"
                         "}";

    ASSERT_FALSE(deleteLibtcc1());

    TCCState *tccState = atcc_new();
    ASSERT_TRUE(tccState);

    tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);

    ASSERT_FALSE(tcc_compile_string(tccState, string));
    ASSERT_FALSE(tcc_relocate(tccState, TCC_RELOCATE_AUTO));

    int (*func)();
    func = reinterpret_cast<int(*)()>(tcc_get_symbol(tccState, "test"));
    ASSERT_TRUE(func);

    ASSERT_EQ(func(), 256);

    tcc_delete(tccState);
    ASSERT_FALSE(deleteLibtcc1());
}

GTEST_TEST(Libtcc_Extension_Compile__Tests, Compile_2) {
    const char* string = "#include<math.h>\n"
                         "int test(int x1, int x2) {\n"
                         "  return pow(x1+x2, x2);\n"
                         "}";

    ASSERT_FALSE(deleteLibtcc1());

    TCCState *tccState = atcc_new();
    ASSERT_TRUE(tccState);

    tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);

    ASSERT_FALSE(tcc_compile_string(tccState, string));

    int size = tcc_relocate(tccState, nullptr);
    void* ptr = malloc(size);
    ASSERT_TRUE(tcc_relocate(tccState, ptr) != -1);

    int (*func)(int, int);
    func = reinterpret_cast<int(*)(int,int)>(tcc_get_symbol(tccState, "test"));
    ASSERT_TRUE(func);

    ASSERT_EQ(func(3, 3), 216);
    ASSERT_EQ(func(2, 3), 125);
    ASSERT_EQ(func(2010, 1), 2011);

    tcc_delete(tccState);

    ASSERT_EQ(func(3, 3), 216);
    ASSERT_EQ(func(2, 3), 125);
    ASSERT_EQ(func(2010, 1), 2011);

    free(ptr);
    ASSERT_FALSE(deleteLibtcc1());
}
