#ifndef KAGEBUNSHIN_CONCURRENTQUEUETESTS_H
#define KAGEBUNSHIN_CONCURRENTQUEUETESTS_H


#include "../src/ConcurrentQueue.h"
#include <gtest/gtest.h>

class ConcurrentQueueTests : public ::testing::Test {
protected:
    ConcurrentQueue<int> concurrentQueue;
};


#endif//KAGEBUNSHIN_CONCURRENTQUEUETESTS_H
