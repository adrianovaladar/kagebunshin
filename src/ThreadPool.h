#ifndef KAGEBUNSHIN_THREADPOOL_H
#define KAGEBUNSHIN_THREADPOOL_H

#include "ConcurrentQueue.h"
#include <functional>
#include <thread>

using Func = std::function<void()>;
/**
 * @brief Thread pool class.
 *
 * This class manages a pool of threads that can execute functions submitted to it.
 */
class ThreadPool {
    ConcurrentQueue<Func> workQueue; /**< The work queue for storing functions to be executed. */
    std::vector<std::thread> threads; /**< The vector of worker threads in the pool. */
    /**
     * @brief Worker function that runs in each thread.
     */
    void worker();

public:
    /**
      * @brief ThreadPool constructor.
      * @param numberThreads The desired number of threads to work concurrently. The default value is equal to the hardware threads.
    */
    explicit ThreadPool(size_t numberThreads = std::thread::hardware_concurrency());
    /**
     * @brief ThreadPool destructor.
     *
     * This destructor joins all worker threads to ensure they finish executing before the pool is destroyed.
    */
    ~ThreadPool();
    /**
     * @brief Submits a function to the thread pool for execution.
     *
     * The function will be added to the work queue and executed by one of the worker threads.
     *
     * @param f The function to be executed.
    */
    void submit(Func f);
    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool(ThreadPool &&other) = delete;
    ThreadPool &operator=(const ThreadPool &other) = delete;
    ThreadPool &operator=(ThreadPool &&other) = delete;
};


#endif//KAGEBUNSHIN_THREADPOOL_H
