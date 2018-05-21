//
// Created by Ben on 21/05/2018.
//

#ifndef OSHW5_RESOLVER_H
#define OSHW5_RESOLVER_H


#include "ThreadPool.h"
#include "SafeQ.h"


class Resolvers : ThreadPool {
private:
    SafeQ<string> *requestQ;

public:
    Resolvers(int count, pthread_mutex_t &coutMutex, SafeQ<string> &requestQue);

};
void *resDomainName(void * ti);

#endif //OSHW5_RESOLVER_H
