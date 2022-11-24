//
// Created by lvjie on 2022/11/24.
//

#include "ThreadStudy.h"
#include "utils/LogUtil.h"
#include <thread>
#include <unistd.h>

#define TAG "ThreadStudy"

void ThreadStudy::threadFunc(const std::string &threadName, int sleepTime) {

    LOGI(TAG, "threadFunc start, threadName: %s, sleep: %d", threadName.c_str(), sleepTime);
    sleep(sleepTime);
    LOGI(TAG, "threadFunc end, threadName: %s, sleep: %d", threadName.c_str(), sleepTime);
}

/**
 * 主线程会等待三个线程都执行完成后，继续执行;
 * 三个线程之间互不影响
 */
void ThreadStudy::testThread() {
    std::thread thread1(threadFunc, "thread-1", 1);
    std::thread thread2(threadFunc, "thread-2", 2);
    std::thread thread3(threadFunc, "thread-3", 3);

    LOGI(TAG, "testThread start.");
    thread1.join();
    thread2.join();
    thread3.join();
    LOGI(TAG, "testThread end.");
}