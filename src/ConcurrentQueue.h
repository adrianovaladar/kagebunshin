#ifndef KAGEBUNSHIN_CONCURRENTQUEUE_H
#define KAGEBUNSHIN_CONCURRENTQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
/**
 * @brief A thread-safe concurrent queue implementation.
 *
 * This class provides a thread-safe implementation of a queue
 * that allows multiple threads to push and pop elements concurrently.
 *
 * @tparam T The type of elements stored in the queue.
 */
template<class T>
class ConcurrentQueue {
    std::mutex mutex;                          /**< Mutex to synchronize access to the queue. */
    std::queue<T> queue;                       /**< The queue managed by this class. */
    std::condition_variable conditionVariable; /**< Condition variable for waiting on empty queue. */
    bool stop{};

public:
    /**
     * @brief Default constructor.
     *
     * Constructs a new ConcurrentQueue object.
     */
    ConcurrentQueue() = default;
    /**
     * @brief Pushes a new element into the queue.
     *
     * @param value The value to be pushed into the queue.
     */
    void push(T value) {
        std::scoped_lock lg(mutex);
        queue.push(value);
        conditionVariable.notify_one();// Notify waiting threads about new data.
    }
    /**
     * @brief Pops an element from the queue.
     *
     * If the queue is empty, the calling thread will wait until an element is available.
     *
     * @param value Reference to store the popped value.
     */
    bool pop(T &value) {
        std::unique_lock lg(mutex);
        conditionVariable.wait(lg, [this] { return !queue.empty() || stop; });// Wait until the queue is not empty or stop is true.
        if (stop)
            return false;
        value = queue.front();
        queue.pop();
        return true;
    }
    /**
     * @brief Terminates the queue operations.
     *
     * This function waits until the queue becomes empty and then sets the stop flag,
     * signaling to stop all queue operations.
     * After setting the stop flag, it notifies all waiting threads.
     */
    void terminate() {
        while (!queue.empty()) {// Wait until the queue becomes empty
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::unique_lock lg(mutex);
        stop = true;
        conditionVariable.notify_all();
    }
    /**
     * @brief Returns a const reference to the queue.
     *
     * This method is intended for debugging or inspection purposes only,
     * as direct access to the queue can compromise thread safety.
     *
     * @return A const reference to the queue.
     */
    const std::queue<T> &getQ() const {
        return queue;
    }
};

#endif// KAGEBUNSHIN_CONCURRENTQUEUE_H
