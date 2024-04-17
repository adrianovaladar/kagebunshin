#ifndef KAGEBUNSHIN_CONCURRENTQUEUE_H
#define KAGEBUNSHIN_CONCURRENTQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

template<class T>
class ConcurrentQueue {
    std::mutex mutex;
    std::queue<T> queue;
    std::condition_variable conditionVariable;

public:
    ConcurrentQueue() = default;
    void push(T value) {
        std::lock_guard<std::mutex> lg(mutex);
        queue.push(value);
        conditionVariable.notify_one();// Notify waiting threads about new data.
    }
    void pop(T &value) {
        std::unique_lock<std::mutex> lg(mutex);
        conditionVariable.wait(lg, [this] { return !queue.empty(); });// Wait until the queue is not empty.
        value = queue.front();
        queue.pop();
    }
    const std::queue<T> &getQ() const {
        return queue;
    }
};

#endif//KAGEBUNSHIN_CONCURRENTQUEUE_H
