#include "LoggerTests.h"
#include <fstream>

TEST_F(LoggerTests, LogMessageTest) {
    logger.log("Test message", LOGLEVEL::Info);

    std::stringstream buffer;
    buffer << logFile.rdbuf();
    std::string logContents = buffer.str();

    ASSERT_NE(std::string::npos, logContents.find("Test message"));
}

TEST_F(LoggerTests, MultipleLogMessagesTest) {
    std::thread threads[std::thread::hardware_concurrency()];
    auto logMessage = [&]() {
        logger.log("Test multithreading message", LOGLEVEL::Info);
    };

    for (int i{}; i < std::thread::hardware_concurrency(); i++)
        threads[i] = std::thread(logMessage);
    for (int i{}; i < std::thread::hardware_concurrency(); i++)
        threads[i].join();

    std::stringstream buffer;
    buffer << logFile.rdbuf();
    std::string logContents = buffer.str();

    for (int i{}; i < std::thread::hardware_concurrency(); i++)
        ASSERT_NE(std::string::npos, logContents.find("Test multithreading message"));
}
