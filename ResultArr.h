//
// Created by Ben on 23/05/2018.
//

#ifndef OSHW5_RESULTARR_H
#define OSHW5_RESULTARR_H

#include "Node.h"

#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <cstring>
#include <unistd.h>
#include "iostream"
#include <pthread.h>
#include <string>
#include <fstream>
using namespace std;

class ResultArr {
private:
    Node* head;
    pthread_mutex_t mutex;
    pthread_mutex_t *coutMutex;
public:

    ResultArr(pthread_mutex_t *coutMutex);

    void push(Node* node);
    Node* pop();
    Node* findNodeByUrl(string *url);
    void print();
};


#endif //OSHW5_RESULTARR_H
