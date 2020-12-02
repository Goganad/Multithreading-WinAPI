cmake_minimum_required(VERSION 3.17)
project(Multithreading_WinAPI)

set(CMAKE_CXX_STANDARD 20)

add_executable(Multithreading_WinAPI main.cpp ConcurrentQueue.h QueueTask.h FileSorter.h FileStitcher.h)