#include "ThreadPoolTests.h"

TEST_F(ThreadPoolTests, SingleTaskExecutionTest) {
    ThreadPool pool{1};
    pool.submit(functionWithArguments);
    sleep(1);

    std::stringstream buffer;
    buffer << logFile.rdbuf();
    std::string logContents = buffer.str();

    ASSERT_NE(std::string::npos, logContents.find(hello) + number);
}

TEST_F(ThreadPoolTests, ConcurrentTaskExecutionTest) {
    int numberTimes{10};
    int count{};
    ThreadPool pool{10};
    for (int i{}; i < numberTimes; i++) {
        pool.submit([this, &count]() {
            std::scoped_lock lock(mutex);
            number++;
            functionWithArguments();
            count++;
        });
    }
    sleep(1);
    for (int i{}; i < numberTimes; i++) {
        logFile.seekg(0, std::ios::beg);
        std::stringstream buffer;
        buffer << logFile.rdbuf();
        std::string logContents = buffer.str();
        ASSERT_NE(std::string::npos, logContents.find(hello + std::to_string(number)));
        number--;
    }
    ASSERT_EQ(count, numberTimes);
}

TEST(ThreadPoolTest, SubmitAndExecuteTasks) {
    int numberTimes{10};
    ThreadPool pool{4};
    int sum{};
    for (int i{}; i < numberTimes; ++i) {
        pool.submit([i, &sum]() {
            sum += i;
        });
    }
    sleep(1);
    for (int i{}; i < numberTimes; ++i) {
        sum -= i;
    }
    ASSERT_EQ(sum, 0);
}
