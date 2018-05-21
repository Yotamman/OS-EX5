//
// Created by Ben on 17/05/2018.
//

#ifndef OSHW5_REQUESTERS_H
#define OSHW5_REQUESTERS_H

#include "ThreadPool.h"
#include "SafeQ.h"

class Requesters : public ThreadPool {

private:
    string files;
    SafeQ<string> *requestQ;


public:
    Requesters(char *files[1], int count, pthread_mutex_t &coutMutex, SafeQ<string> &requestQue);

    //this method open the file and exports the domain name as Tasks into the tasks SafeQueue
   // void *getDomainName(void * fileName);

    void *PrintHello(void *threadid);
};

void *getDomainName(void * ti);
#endif //OSHW5_REQUESTERS_H
