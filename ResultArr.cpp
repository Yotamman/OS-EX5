//
// Created by Ben on 23/05/2018.
//

#include <pthread.h>
#include "ResultArr.h"

ResultArr::ResultArr(pthread_mutex_t *coutMutex) {
    this->head=NULL;
    this->coutMutex=coutMutex;
}

void ResultArr::push(Node *node) {
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(node->getTask()->getCond());      //notify the requester that create the task
    //cout<<"push:"<<node->getTask()->getCond();
    if(head==NULL){
        head=node;
        pthread_mutex_unlock (&mutex);



        return;
    }
    Node* tmp=head;
    while(tmp->getNext()!=NULL){
        tmp=tmp->getNext();
    }
    tmp->setNext(node);
    pthread_mutex_unlock (&mutex);
    return;
}

Node *ResultArr::pop() {
    pthread_mutex_lock(&mutex);
    if(head==NULL){
        pthread_mutex_unlock (&mutex);
        return NULL;
    }
    Node* tmp=head;
    head=head->getNext();
    pthread_mutex_unlock (&mutex);
    return tmp;
}

Node *ResultArr::findNodeByUrl(string *url) {

    pthread_mutex_lock(&mutex);
    if(head==NULL){
        pthread_mutex_unlock (&mutex);
        return NULL;
    }
    Node *tmp=head;
    while(tmp->getNext()!=NULL){                    //compare by address
        if(tmp->getTask()->getUrl()==url){
            pthread_mutex_unlock (&mutex);
            return tmp;
        }
        tmp=tmp->getNext();
    }
    pthread_mutex_unlock (&mutex);
    return NULL;
}

void ResultArr::print() {
    pthread_mutex_lock(this->coutMutex);
    Node *tmp=head;
    while(tmp->getNext()!=NULL){                    //compare by address
        cout<<" ResultArr: url: "<<tmp->getTask()->getUrl()<<"\n";
        }
    pthread_mutex_unlock(this->coutMutex);
}

