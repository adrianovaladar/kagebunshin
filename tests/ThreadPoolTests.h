#ifndef KAGEBUNSHIN_THREADPOOLTESTS_H
#define KAGEBUNSHIN_THREADPOOLTESTS_H

#include "../src/ThreadPool.h"
#include <format>
#include <fstream>
#include <gtest/gtest.h>

const std::string hello{"Hello from function"};
const std::string fileName{"test_file.txt"};

class ThreadPoolTests : public ::testing::Test {
protected:
    void singleTaskExecutionTest(size_t numberThreads);
    std::function<void()> functionWithArguments;
    std::fstream file;
    int number{};
    std::mutex mutex;
    void SetUp() override {
        file.open(fileName, std::ios::in | std::ios::out | std::ios::app);
        if (!file.is_open()) {
            FAIL() << "Failed to open log file: " << fileName;
        }
        functionWithArguments = [this]() { return function(number); };
    }

    void TearDown() override {
        file.close();
        std::remove(fileName.c_str());
    }

    void function(const int n) {
        file << std::format("{} {}\n", hello, n);
    }
};


#endif//KAGEBUNSHIN_THREADPOOLTESTS_H
