//
// Created by Ben on 23/05/2018.
//

#ifndef OSHW5_NODE_H
#define OSHW5_NODE_H
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <cstring>
#include <unistd.h>
#include "iostream"
#include "Task.h"
#include <pthread.h>
#include <string>
#include <fstream>
using namespace std;

class Node {
private:
    Node* next;
    Task *task;
public:
    Node(Task *task);
    void setNext(Node *next);
    Node *getNext() const;
    Task *getTask() const;
    void setTask(Task *task);
};

#endif //OSHW5_NODE_H