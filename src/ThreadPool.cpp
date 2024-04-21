#include "ThreadPool.h"
#include <iostream>

void ThreadPool::worker() {
    while (true) {
        Func task;
        if (!workQueue.pop(task))
            return;
        task();
    }
}

ThreadPool::ThreadPool(size_t numberThreads) {
    for (unsigned i = 0; i < numberThreads; i++)
        threads.emplace_back(&ThreadPool::worker, this);
}

ThreadPool::~ThreadPool() {
    workQueue.terminate();
    for (auto &t: threads) {
        t.join();
    }
}

void ThreadPool::submit(Func f) {
    workQueue.push(std::move(f));
}
