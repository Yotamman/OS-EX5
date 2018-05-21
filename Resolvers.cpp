//
// Created by Ben on 21/05/2018.
//

#include "Resolvers.h"
typedef struct ThreadData {
    int tid;
    //pthread_mutex_t *coutMutex;
    SafeQ<string> *requestQ;
    pthread_mutex_t *coutMutex;
} ThreadInfo;


Resolvers::Resolvers(int count, pthread_mutex_t &coutMutex, SafeQ<string> &requestQue): ThreadPool(count,coutMutex) {
    int rc;
    void *res;
    for(int i=0; i<count ; i++){
        ThreadData *tData = new ThreadData();
        tData->tid=i; //build the data and id for the thread
        tData->coutMutex=this->coutMutex;
        tData->requestQ=&requestQue;
        rc=pthread_create(threads[i], NULL, resDomainName, (void*)tData);
        pthread_join(*threads[i], &res);
    }


}

//multi-threading function
void * resDomainName(void * tData) {
    ThreadData *fn= (ThreadData*)tData;          //convert the tData to struct
    cout<<*fn->requestQ->deQ()<<'\n';
    fn->requestQ->print();

    pthread_exit(NULL);
}

