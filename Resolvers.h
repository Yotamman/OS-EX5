//
// Created by Ben on 21/05/2018.
//

#ifndef OSHW5_RESOLVER_H
#define OSHW5_RESOLVER_H


#include "ThreadPool.h"
#include "SafeQ.h"
#include "ResultArr.h"
#include <cstring>
#include <thread>
#include <chrono>
#define MAX_ADDRESSES 10    //number of address for ine url
#define UTIL_FAILURE -1
#define UTIL_SUCCESS 0


class Resolvers : ThreadPool {
private:
    SafeQ<Task> *requestQ;


public:
    Resolvers(int count, pthread_mutex_t &coutMutex, SafeQ<Task> &requestQue, ResultArr &resultArr);

};
void *resDomainName(void * ti);
int dns(const char* hostname,char *firstIPstr,int maxSize);
#endif //OSHW5_RESOLVER_H
