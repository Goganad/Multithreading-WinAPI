#ifndef MULTITHREADING_WINAPI_CONCURRENTQUEUE_H
#define MULTITHREADING_WINAPI_CONCURRENTQUEUE_H

#include <vector>
#include <string>
#include <mutex>
#include <queue>
#include "QueueTask.h"

using namespace std;

class ConcurrentQueue {

private:
    queue<QueueTask> taskQueue;
    mutable mutex mutex;

public:
    void enqueue(QueueTask &value) {
        lock_guard<std::mutex> lock(mutex);
        taskQueue.push(value);
    }

    QueueTask dequeue() {
        lock_guard<std::mutex> lock(mutex);
        QueueTask ret = taskQueue.front();
        taskQueue.pop();
        return ret;
    }

    int getSize() {
        lock_guard<std::mutex> lock(mutex);
        return taskQueue.size();
    }
};

#endif
