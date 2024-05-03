#ifndef TEXTFINDERTESTS_H
#define TEXTFINDERTESTS_H

#include <gtest/gtest.h>
#include "../src/TextFinder.h"
#include <fstream>

class TextFinderTests : public ::testing::Test {
protected:
    TextFinder tf;
    std::filesystem::path path {std::filesystem::current_path() / "directory"};
    std::string text  {"hello"};
    void SetUp() override {
        std::filesystem::create_directory(path);
        std::ofstream outputFile("directory/example.txt");
        outputFile << text;
    }

    void TearDown() override {
        std::filesystem::remove_all(path);
    }
};



#endif //TEXTFINDERTESTS_H
