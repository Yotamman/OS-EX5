//
// Created by Ben on 17/05/2018.
//
#include <unistd.h>
#include <thread>
#include <chrono>
#include <condition_variable>
#include "Requesters.h"
#define MAX_NAME_LENGTH 1025

typedef struct ThreadData {
    int tid;
    char* fn;
    pthread_mutex_t *coutMutex;
    SafeQ<Task> *requestQ;
    pthread_cond_t *cond;
} ThreadInfo;

condition_variable cvArr;

Requesters::Requesters(char *files[1], int tCount, pthread_mutex_t &coutMutex, SafeQ<Task> &requestQue, ResultArr &resultArr) : ThreadPool(tCount, coutMutex, &resultArr) {
        int rc;
        void *res;
        this->condPerThread= new pthread_cond_t[tCount];


        for(int i=0; i<tCount ; i++){
            ThreadData *tData = new ThreadData();
            tData->fn=files[i];         //build the data and id for the thread
            tData->tid=i;
            tData->coutMutex=this->coutMutex;
            tData->requestQ=&requestQue;
            pthread_cond_init(&this->condPerThread[i],NULL);
            tData->cond=&this->condPerThread[i];
            rc=pthread_create(threads[i], NULL, getDomainName, (void*)tData);
    }
//    //waiting for all threads to finish
//    for(int i=0; i<tCount ; i++){
//        pthread_join(*threads[i], &res);
//        }
//     cout<< "\n"<<"All Requester Threads done to read"<<"\n"  ;
}

    //multi-threading function
void * getDomainName(void * tData){

    ThreadData *fn= (ThreadData*)tData;          //convert the tData to struct
    char*  fileName=fn->fn;                      //extract the fileName from tData
    pthread_mutex_t *coutMutex=fn->coutMutex;    //extract the mutex from tData

    string line;
    ifstream infile(fileName);                 //open the file with the file name
    int waitTime;
    while (getline(infile, line)) {
        string *url= new string(line);


        while(!fn->requestQ->enQ(new Task(NULL,url,fn->cond))){     //push new Task into the queue
            waitTime = rand()%100;         //if the url didn't get into the queue: wait rand time and try again;
            this_thread::sleep_for(chrono::microseconds(waitTime));
        }
        //print every line it read from the file
        pthread_mutex_lock(fn->coutMutex);
        cout<<"Requester "<<fn->tid<<" push: "<<*url<<"\n";
        pthread_mutex_unlock(fn->coutMutex);

        pthread_cond_wait(fn->cond,NULL);       //the thread wait until the task is been push into the result array

    }
    //finish section
        pthread_mutex_lock(fn->coutMutex);
        cout << "System: Requester "<<fn->tid<<" finish the file !\n";   //the thread finish to read all the file
        pthread_mutex_unlock(fn->coutMutex);
    pthread_exit(NULL);
}

