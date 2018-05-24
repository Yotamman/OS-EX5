//
// Created by Ben on 17/05/2018.
//

#ifndef OSHW5_THREADPOOL_H
#define OSHW5_THREADPOOL_H

#include "Task.h"
#include "iostream"
#include "ResultArr.h"
#include <pthread.h>
#include <string>
#include <fstream>
using namespace std;

class ThreadPool {
protected:
    ResultArr *resultArr;
    pthread_t **threads;
    pthread_mutex_t mutex;
    pthread_mutex_t *coutMutex;

    int threadNum;

public:
    ThreadPool(int threadNum,pthread_mutex_t &coutMutex, ResultArr *resultArr);


};


#endif //OSHW5_THREADPOOL_H
