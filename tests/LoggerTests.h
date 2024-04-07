#ifndef KAGEBUNSHIN_LOGGERTESTS_H
#define KAGEBUNSHIN_LOGGERTESTS_H

#include "../src/Logger.h"
#include <gtest/gtest.h>

// Define a test fixture class
class LoggerTest : public ::testing::Test {
public:
    LoggerTest() : logger(Logger::getInstance()) {}

protected:
    // Set up common data or objects before each test case
    void SetUp() override {
        // Initialize any resources needed for testing
    }

    // Clean up after each test case
    void TearDown() override {
        // Release any resources allocated during testing
    }

    Logger &logger;
};


#endif//KAGEBUNSHIN_LOGGERTESTS_H
