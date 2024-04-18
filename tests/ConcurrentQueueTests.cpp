#include "ConcurrentQueueTests.h"

TEST_F(ConcurrentQueueTests, PushAndPopTest) {
    int iterations{3};
    for (int i{}; i < iterations; i++) {
        concurrentQueue.push(i);
    }
    for (int i{}; i < iterations; i++) {
        int value{};
        concurrentQueue.pop(value);
        ASSERT_EQ(value, i);
    }
}

TEST_F(ConcurrentQueueTests, MultithreadedPushAndPopTest) {
    auto push = [&](int count) {
        for (int i{}; i < count; ++i) {
            concurrentQueue.push(i);
        }
    };
    auto pop = [&](int count) {
        int value;
        for (int i{}; i < count; ++i) {
            concurrentQueue.pop(value);
            ASSERT_GE(value, 0);
            ASSERT_LE(value, count);
        }
    };
    int count{100};
    std::thread pushThread(push, count);
    std::thread popThread(pop, count);
    pushThread.join();
    popThread.join();
}

TEST_F(ConcurrentQueueTests, StressTest) {
    constexpr int numThreads = 100;
    constexpr int numElementsPerThread = 1000;
    std::mutex mutex;
    auto pushPop = [&] {
        for (int i = 0; i < numElementsPerThread; i++) {
            std::lock_guard<std::mutex> lock(mutex);
            concurrentQueue.push(i);
            int value;
            concurrentQueue.pop(value);
            ASSERT_EQ(value, i);
        }
    };
    std::vector<std::thread> threads(numThreads);
    for (auto &thread: threads) {
        thread = std::thread(pushPop);
    }
    for (auto &thread: threads) {
        thread.join();
    }
    ASSERT_EQ(concurrentQueue.getQ().size(), 0);
}

TEST_F(ConcurrentQueueTests, InitiallyEmptyQueueTest) {
    ASSERT_EQ(concurrentQueue.getQ().size(), 0);
}
