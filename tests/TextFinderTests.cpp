#include "TextFinderTests.h"

TEST_F(TextFinderTests, FindWithDirectoryThatDoesNotExist) {
    EXPECT_ANY_THROW(tf.find("/directory/that/does/not/exist", {"text"}));
}

TEST_F(TextFinderTests, FindWithoutWords) {
    EXPECT_ANY_THROW(tf.find(std::string(path), {}));
}

TEST_F(TextFinderTests, FindSuccessfully) {
    tf.find(std::string(path), {text});
    ASSERT_GE(tf.getFoundFiles().size(), 1);
}

TEST_F(TextFinderTests, FindUnsuccessfully) {
    tf.find(std::string(path), {text + "abc"});
    ASSERT_EQ(tf.getFoundFiles().size(), 0);
}
