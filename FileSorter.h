#ifndef MULTITHREADING_WINAPI_FILESORTER_H
#define MULTITHREADING_WINAPI_FILESORTER_H

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <thread>
#include "QueueTask.h"
#include "ConcurrentQueue.h"
#include "FileStitcher.h"

using namespace std;

class FileSorter {
private:
    ConcurrentQueue sortQueue = ConcurrentQueue();

    vector<vector<string>> sortedLinesSubvecs;

    void thread() {
        if (sortQueue.getSize() > 0) {
            QueueTask task = sortQueue.dequeue();
            task.perform();
            sortedLinesSubvecs.emplace_back(task.lines);
        }
    }

    static long static_thread_entry(void *param) {
        auto *myObj = (FileSorter *) param;
        myObj->thread();
        return 0;
    }

    void sort(int threadCount) {
        int linesCount = initial.size();
        if (linesCount < threadCount) {
            threadCount = linesCount;
        }

        int linesLeft = linesCount;
        int tasksCount = linesCount / threadCount;

        for (int i = 0; i < threadCount; i++) {
            vector<string>::const_iterator start;
            vector<string>::const_iterator end;

            if (i < threadCount - 1) {
                start = initial.begin() + i * tasksCount;
                end = start + tasksCount;
                linesLeft -= tasksCount;
            } else {
                end = initial.end();
                start = end - linesLeft;
            }

            QueueTask task = QueueTask(vector<string>(start, end));
            sortQueue.enqueue(task);
        }

        HANDLE hThreads[threadCount];
        for (int i = 0; i < threadCount; i++) {
            hThreads[i] = CreateThread(nullptr,0, (LPTHREAD_START_ROUTINE) (&static_thread_entry),this, 0,nullptr);
        }
        WaitForMultipleObjects(threadCount, hThreads, TRUE, INFINITE);

        for (auto &subvec : sortedLinesSubvecs) {
            for (const string &line : subvec) {
                sorted.emplace_back(line + '\n');
            }
            FileStitcher::sort(sorted.data(), sorted.size());
        }

        sortedLinesSubvecs.clear();
    }

public:
    vector<string> initial;
    vector<string> sorted;

    explicit FileSorter(const vector<string> &lines, int threadCount) {
        initial = lines;
        if (threadCount > 0 && !initial.empty()) {
            sort(threadCount);
        } else {
            throw runtime_error("File empty or thread count <= 0");
        }
    }
};


#endif
