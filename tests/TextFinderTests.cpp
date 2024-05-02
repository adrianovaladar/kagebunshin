#include "TextFinderTests.h"

TEST_F(TextFinderTests, FindWithDirectoryThatDoesNotExist) {
    tf.find("/directory/that/does/not/exist", {"text"});
    ASSERT_EQ(tf.getFoundFiles().size(), 0);
}
