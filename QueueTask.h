#ifndef MULTITHREADING_WINAPI_QUEUETASK_H
#define MULTITHREADING_WINAPI_QUEUETASK_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class QueueTask {
public:
    bool completed = false;
    vector<string> lines;

    explicit QueueTask(const std::vector<std::string> &lines) {
        this->lines = lines;
    }

    void perform() {
        if (!completed) {
            sort(lines.begin(), lines.end());
            completed = true;
        }
    }
};


#endif
