#include "LoggerTests.h"
#include <fstream>

TEST_F(LoggerTest, LogMessageTest) {
    Logger &logger = Logger::getInstance();
    logger.log("Test message", LOGLEVEL::Info);

    std::ifstream logFile(logger.getLogFileName());
    std::stringstream buffer;
    buffer << logFile.rdbuf();
    std::string logContents = buffer.str();

    ASSERT_NE(std::string::npos, logContents.find("Test message"));
}
