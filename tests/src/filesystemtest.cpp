#include "gtest/gtest.h"

#include "../../extension/src/private/filesystem.h"


GTEST_TEST(Filesystem_Tests, get_file_content)
{
    char* content = atcc_get_file_content("imaginary/imaginary-file.imag");
    ASSERT_EQ(content, nullptr);
    content = atcc_get_file_content("test/test.txt");
    ASSERT_STREQ(content, "This is a test file for filesystem.h\n\nThis should be read by the unit test");
    free(content);
}
