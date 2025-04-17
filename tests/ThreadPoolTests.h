#ifndef KAGEBUNSHIN_THREADPOOLTESTS_H
#define KAGEBUNSHIN_THREADPOOLTESTS_H

#include "../src/ThreadPool.h"
#include <logorithm/Logger.h>
#include <format>
#include <fstream>
#include <gtest/gtest.h>

const std::string hello{"Hello from function"};

inline void function(const int number) {
    logger.log(std::format("{} {}", hello, number), LOGLEVEL::Info);
}

class ThreadPoolTests : public ::testing::Test {
protected:
    void singleTaskExecutionTest(size_t numberThreads) const;
    std::function<void()> functionWithArguments;
    std::ifstream logFile;
    int number{};
    std::mutex mutex;
    void SetUp() override {
        logFile.open(logger.getLogFileName());
        if (!logFile.is_open()) {
            FAIL() << "Failed to open log file: " << logger.getLogFileName();
        }
        functionWithArguments = [this]() { return function(number); };
    }

    void TearDown() override {
        logFile.close();
    }
};


#endif//KAGEBUNSHIN_THREADPOOLTESTS_H
