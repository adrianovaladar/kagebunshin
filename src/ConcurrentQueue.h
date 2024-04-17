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
        std::lock_guard<std::mutex> lg(mutex);
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
    void pop(T &value) {
        std::unique_lock<std::mutex> lg(mutex);
        conditionVariable.wait(lg, [this] { return !queue.empty(); });// Wait until the queue is not empty.
        value = queue.front();
        queue.pop();
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
