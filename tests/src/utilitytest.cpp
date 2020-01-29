#include "gtest/gtest.h"

#include "../../extension/src/private/utility.h"

GTEST_TEST(Utility_Tests, concatenate_path)
{
    char* path = atcc_concatenate_path(nullptr, "file", "extension");
    ASSERT_EQ(path, nullptr);
    path = atcc_concatenate_path("/this/is/a/path/to/", nullptr, "extension");
    ASSERT_EQ(path, nullptr);

    path = atcc_concatenate_path("/this/is/a/path/to/", "file", nullptr);
    ASSERT_STREQ(path, "/this/is/a/path/to/file");
    free(path);
    path = atcc_concatenate_path("/this/is/a/path/to/", "file", "");
    ASSERT_STREQ(path, "/this/is/a/path/to/file");
    free(path);

    path = atcc_concatenate_path("/this/is/a/path/to/", "file", "extension");
    ASSERT_STREQ(path, "/this/is/a/path/to/file.extension");
    free(path);

    path = atcc_concatenate_path("////this///is//a//path/to///////", "file", "extension");
    ASSERT_STREQ(path, "/this/is/a/path/to/file.extension");
    free(path);

    path = atcc_concatenate_path("/this/is/a/path/to", "file", "extension");
    ASSERT_STREQ(path, "/this/is/a/path/to/file.extension");
    free(path);
}

GTEST_TEST(Utility_Tests, split_string__splitted_string_length__free_splitted_string)
{
    char** splitted = atcc_split_string(NULL, '.');
    ASSERT_EQ(splitted, nullptr);
    splitted = atcc_split_string("", '.');
    ASSERT_EQ(splitted, nullptr);

    splitted = atcc_split_string("this.is.a.test", '.');
    ASSERT_EQ(atcc_splitted_string_length(splitted), 4);
    ASSERT_STREQ(splitted[0], "this");
    ASSERT_STREQ(splitted[1], "is");
    ASSERT_STREQ(splitted[2], "a");
    ASSERT_STREQ(splitted[3], "test");
    atcc_free_splitted_string(splitted);

    splitted = atcc_split_string("/this/is/a/test/", '/');
    ASSERT_EQ(atcc_splitted_string_length(splitted), 4);
    ASSERT_STREQ(splitted[0], "this");
    ASSERT_STREQ(splitted[1], "is");
    ASSERT_STREQ(splitted[2], "a");
    ASSERT_STREQ(splitted[3], "test");
    atcc_free_splitted_string(splitted);

    ASSERT_EQ(atcc_splitted_string_length(NULL), 0);
}
