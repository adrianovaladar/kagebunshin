#include "ThreadPoolTests.h"

void ThreadPoolTests::singleTaskExecutionTest(size_t numberThreads) {
    ThreadPool pool{numberThreads};
    pool.submit(functionWithArguments);
    sleep(1);

    file.seekg(0, std::ios::beg);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    ASSERT_NE(std::string::npos, contents.find(std::format("{} {}", hello, number)));
}

TEST_F(ThreadPoolTests, SingleTaskExecutionTestWithOneThread) {
    singleTaskExecutionTest(1);
}

TEST_F(ThreadPoolTests, SingleTaskExecutionTestWithOneThreadButPassingZero) {
    singleTaskExecutionTest(0);
}

TEST_F(ThreadPoolTests, ConcurrentTaskExecutionTest) {
    constexpr int numberTimes{10};
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
        file.seekg(0, std::ios::beg);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string contents = buffer.str();
        ASSERT_NE(std::string::npos, contents.find(std::format("{} {}", hello, number)));
        number--;
    }
    ASSERT_EQ(count, numberTimes);
}

TEST(ThreadPoolTest, SubmitAndExecuteTasks) {
    constexpr int numberTimes{10};
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
