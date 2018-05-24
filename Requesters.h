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
    SafeQ<Task> *requestQ;
    pthread_cond_t *condPerThread;
    


public:
    Requesters(char *files[1], int tCount, pthread_mutex_t &coutMutex, SafeQ<Task> &requestQue, ResultArr &resultArr);

    //this method open the file and exports the domain name as Tasks into the tasks SafeQueue
   // void *getDomainName(void * fileName);

};

void *getDomainName(void * ti);

#endif //OSHW5_REQUESTERS_H
