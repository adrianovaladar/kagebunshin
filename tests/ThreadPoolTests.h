#ifndef KAGEBUNSHIN_THREADPOOLTESTS_H
#define KAGEBUNSHIN_THREADPOOLTESTS_H

#include "../src/Logger.h"
#include "../src/ThreadPool.h"
#include <gtest/gtest.h>

class ThreadPoolTests : public ::testing::Test {
protected:
    std::ifstream logFile;
    void SetUp() override {
        logFile.open(logger.getLogFileName());
        if (!logFile.is_open()) {
            FAIL() << "Failed to open log file: " << logger.getLogFileName();
        }
    }

    void TearDown() override {
        logFile.close();
    }
};


#endif//KAGEBUNSHIN_THREADPOOLTESTS_H
