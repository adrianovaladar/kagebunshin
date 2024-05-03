#include "TextFinderTests.h"

TEST_F(TextFinderTests, FindWithDirectoryThatDoesNotExist) {
    tf.find("/directory/that/does/not/exist", {"text"});
    ASSERT_EQ(tf.getFoundFiles().size(), 0);
}

TEST_F(TextFinderTests, FindWithoutWords) {
    tf.find(std::string(path), {});
    ASSERT_EQ(tf.getFoundFiles().size(), 0);
}

TEST_F(TextFinderTests, FindSuccessfully) {
    tf.find(std::string(path), {text});
    ASSERT_GE(tf.getFoundFiles().size(), 1);
}

TEST_F(TextFinderTests, FindUnsuccessfully) {
    tf.find(std::string(path), {text + "abc"});
    ASSERT_EQ(tf.getFoundFiles().size(), 0);
}
