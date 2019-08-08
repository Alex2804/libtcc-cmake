#include "gtest/gtest.h"

#include "tcc/libtcc.h"

TEST(TccCompileTests, TccCompileTest1) {
    const char* string = "#include<math.h>\n"
                         "int test() {\n"
                         "  return pow(4, 4);\n"
                         "}";

    TCCState *tccState = tcc_new();
    ASSERT_TRUE(tccState);

    tcc_add_library_path(tccState, "lib");
    tcc_set_lib_path(tccState, "lib");
    tcc_add_include_path(tccState, "include");

    tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);

    ASSERT_FALSE(tcc_compile_string(tccState, string));
    ASSERT_FALSE(tcc_relocate(tccState, TCC_RELOCATE_AUTO));

    int (*func)();
    func = reinterpret_cast<int(*)()>(tcc_get_symbol(tccState, "test"));
    ASSERT_TRUE(func);
    ASSERT_EQ(func(), 256);
}

TEST(TccCompileTests, TccCompileTest2) {
    const char* string = "#include<math.h>\n"
                         "int test(int x1, int x2) {\n"
                         "  return pow(x1+x2, x2);\n"
                         "}";

    TCCState *tccState = tcc_new();
    ASSERT_TRUE(tccState);

    tcc_add_library_path(tccState, "lib");
    tcc_set_lib_path(tccState, "lib");
    tcc_add_include_path(tccState, "include");

    tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);

    ASSERT_FALSE(tcc_compile_string(tccState, string));
    ASSERT_FALSE(tcc_relocate(tccState, TCC_RELOCATE_AUTO));

    int (*func)(int, int);
    func = reinterpret_cast<int(*)(int,int)>(tcc_get_symbol(tccState, "test1"));
    ASSERT_FALSE(func);

    func = reinterpret_cast<int(*)(int,int)>(tcc_get_symbol(tccState, "test"));
    ASSERT_TRUE(func);

    ASSERT_EQ(func(3, 3), 216);
    ASSERT_EQ(func(2, 3), 125);
    ASSERT_EQ(func(2010, 1), 2011);
}