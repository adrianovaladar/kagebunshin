#include "ThreadPoolTests.h"

const std::string hello{"Hello from function"};

void function() {
    logger.log(hello, LOGLEVEL::Info);
}

TEST_F(ThreadPoolTests, SubmitTest) {
    ThreadPool pool{1};
    pool.submit(function);
    sleep(1);

    std::stringstream buffer;
    buffer << logFile.rdbuf();
    std::string logContents = buffer.str();

    ASSERT_NE(std::string::npos, logContents.find(hello));
}
