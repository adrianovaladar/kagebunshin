#ifndef KAGEBUNSHIN_THREADPOOL_H
#define KAGEBUNSHIN_THREADPOOL_H

#include "ConcurrentQueue.h"
#include <functional>
#include <thread>

using Func = std::function<void()>;

class ThreadPool {
    ConcurrentQueue<Func> workQueue;
    std::vector<std::thread> threads;
    void worker();

public:
    explicit ThreadPool(size_t numberThreads = std::thread::hardware_concurrency());
    ~ThreadPool();
    void submit(Func f);
};


#endif//KAGEBUNSHIN_THREADPOOL_H
