//
// Created by Ben on 17/05/2018.
//
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Requesters.h"
#define MAX_NAME_LENGTH 1025

typedef struct ThreadData {
    int tid;
    char* fn;
    pthread_mutex_t *coutMutex;
    SafeQ<string> *requestQ;
} ThreadInfo;



Requesters::Requesters(char *files[1], int count,pthread_mutex_t &coutMutex, SafeQ<string> &requestQue) : ThreadPool(count,coutMutex) {
        int rc;
        void *res;
        for(int i=0; i<count ; i++){
            ThreadData *tData = new ThreadData();
            tData->fn=files[i];         //build the data and id for the thread
            tData->tid=i;
            tData->coutMutex=this->coutMutex;
            tData->requestQ=&requestQue;
            rc=pthread_create(threads[i], NULL, getDomainName, (void*)tData);
            pthread_join(*threads[i], &res);
    }
}

    //multi-threading function
void * getDomainName(void * tData){

    ThreadData *fn= (ThreadData*)tData;          //convert the tData to struct
    char*  fileName=fn->fn;                      //extract the fileName from tData
    pthread_mutex_t *coutMutex=fn->coutMutex;    //extract the mutex from tData

    string line;
    ifstream infile(fileName);
    int waitTime;
    while (getline(infile, line)) {
        string *url= new string(line);
        fn->requestQ->enQ(url);
//        while(!fn->requestQ->enQ(url)){
//            //if the url didnt get into the queue wait rand time and try again;
//            waitTime = rand()%100;
//            auto start = chrono::high_resolution_clock::now();
//            this_thread::sleep_for(chrono::microseconds(waitTime));
//            auto finish = chrono::high_resolution_clock::now();
//           // cout << chrono::duration_cast<chrono::microseconds>(finish-start).count() << "us\n";
//        }
    }
        //fn->requestQ->print();

    pthread_exit(NULL);
}

void *Requesters::PrintHello(void *threadid) {
    char* tid;
    tid = (char*)threadid;
    cout << tid << endl;
    pthread_exit(NULL);
}
