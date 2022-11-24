//
// Created by lvjie on 2022/11/24.
//

#ifndef MYJNISTUDYPROJECT_THREADSTUDY_H
#define MYJNISTUDYPROJECT_THREADSTUDY_H

#include <string>

class ThreadStudy {

public:
    static void threadFunc(const std::string &threadName, int sleepTime);

    static void testThread();
};


#endif //MYJNISTUDYPROJECT_THREADSTUDY_H
