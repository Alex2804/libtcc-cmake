#include "gtest/gtest.h"

#include "tcc/libtcc_ext.h"

#include <fstream>

/* returns 0 if file was removed successfully (or hasn't existed) or non zero value if not */
int deleteLibtcc1()
{
    std::FILE *libtcc1_file;
    std::string path = std::string(ALIBTCC1_DEST_PATH) + TCC_LIBTCC1;
    libtcc1_file = std::fopen(path.c_str(), "r");
    if (libtcc1_file) {
        std::fclose(libtcc1_file);
        return remove(path.c_str());
    }
    return 0;
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

    ASSERT_NE(tcc_compile_string(tccState, string), -1);
    ASSERT_NE(tcc_relocate(tccState, TCC_RELOCATE_AUTO), -1);

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

    ASSERT_NE(tcc_compile_string(tccState, string), -1);

    int size = tcc_relocate(tccState, nullptr);
    void* codeBuffer = malloc(size);
    ASSERT_NE(tcc_relocate(tccState, codeBuffer), -1);

    int (*func)(int, int);
    func = reinterpret_cast<int(*)(int,int)>(tcc_get_symbol(tccState, "test"));
    ASSERT_TRUE(func);

    ASSERT_EQ(func(3, 3), 216);
    ASSERT_EQ(func(2, 3), 125);
    ASSERT_EQ(func(2010, 1), 2011);

    tcc_delete(tccState);

    // with MSVC you get an exception with error code 0xc0000005 (access violation) when you call a function after
    // tcc_delete even if relocated (and therefore copied) to extra buffer (in this case codeBuffer).
#ifndef _MSC_VER
    ASSERT_EQ(func(3, 3), 216);
    ASSERT_EQ(func(2, 3), 125);
    ASSERT_EQ(func(2010, 1), 2011);
#endif

    free(codeBuffer);

    ASSERT_FALSE(deleteLibtcc1());
}

std::string errorString;

void errorStringErrorFunction(void *opaque, const char *msg)
{
    errorString.append("an error occured: ").append(msg).append("!!!\n");
}

GTEST_TEST(Libtcc_Extension_atcc_set_error_func_Tests, Compile_2) {
    const char* string = "#include<math.h>\n"
                         "int test(int x1, int x2) {\n"
                         "  return pow(x1+x2, x2);\n"
                         "}";

    atcc_set_error_func(nullptr, errorStringErrorFunction);
    TCCState* tccState = atcc_new();
    ASSERT_TRUE(tccState);
    ASSERT_FALSE(deleteLibtcc1());

    ASSERT_TRUE(errorString.empty());

    tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);
    tcc_compile_string(tccState, string);
    ASSERT_EQ(tcc_relocate(tccState, TCC_RELOCATE_AUTO), -1);

    ASSERT_FALSE(errorString.empty());

    tcc_delete(tccState);


    errorString.clear();
    atcc_set_error_func(reinterpret_cast<void*>(32), nullptr);
    tccState = atcc_new();
    ASSERT_TRUE(tccState);
    ASSERT_FALSE(deleteLibtcc1());

    ASSERT_TRUE(errorString.empty());

    tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);
    tcc_compile_string(tccState, string);
    ASSERT_EQ(tcc_relocate(tccState, TCC_RELOCATE_AUTO), -1);

    ASSERT_TRUE(errorString.empty());

    tcc_delete(tccState);

    ASSERT_FALSE(deleteLibtcc1());
}