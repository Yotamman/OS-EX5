//
// Created by Ben on 16/05/2018.
//

#ifndef OSHW5_SAFEQ_H
#define OSHW5_SAFEQ_H


#include <sys/param.h>
#include <pthread.h>

using namespace std;


template<class T>
class SafeQ {

private:
    string **tasks;
    int len;
    int head;
    int tail;
    int amount;
    pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;

public:
    SafeQ(int length);
    ~SafeQ();
    bool isFull() { return head == (tail + 1) % this->len; }
    bool isEmpty() { return head == tail; }
    bool enQ(T *task);
    void print();
    T *deQ();
};

template<class T>
SafeQ<T>::SafeQ(int length) {
    tasks = new string *[length+1];              //implementation of queue include 1 cell empty
    this->len = length+1;
    head = 0;
    tail = 0;
    for (int i=0; i<length ; i++)               //init
        tasks[i]=NULL;
}

//bool function that return if the push action is successful
template<class T>
bool SafeQ<T>::enQ(T *task) {
    //critical section
    pthread_mutex_lock(&mute);              //lock the mutex mute
    if (isFull()) {                          //if the queue is full
        pthread_mutex_unlock(&mute);        //unlock mutex mute
        return false;
    }
    tasks[tail] = task;                      //inset the task into the queue
    tail++;
    pthread_mutex_unlock(&mute);            //unlock
    return true;
}

//the function return a task. if the queue is empty: return NULL
template<class T>
T* SafeQ<T>::deQ() {
    pthread_mutex_lock(&mute);          //lock the mutex
    if (isEmpty()) {                      //if the arr is empty
        pthread_mutex_unlock(&mute);    //unlock
        return NULL;
    }
    T *tmp;
    tmp = tasks[head];
    head = (head + 1) % len;
    pthread_mutex_unlock(&mute);
    return tmp;
}


template<class T>
SafeQ<T>::~SafeQ() {
    delete[]tasks;
    pthread_mutex_destroy(&mute);
}

template<class T>
void SafeQ<T>::print() {
    pthread_mutex_lock(&mute);          //lock the mutex
    int i= head;
    int postion=1;
    while (i!=tail){
        cout<<postion<<". "<<*tasks[i]<<"\n";
        i++;
        postion++;
        if(i>len)
            i=0;
    }
    pthread_mutex_unlock(&mute);

}


#endif //OSHW5_SAFEQ_H
