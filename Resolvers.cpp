//
// Created by Ben on 21/05/2018.
//

#include <unistd.h>
#include "Resolvers.h"
#include "util.h"


typedef struct ThreadData {
    int tid;
    //pthread_mutex_t *coutMutex;
    SafeQ<Task> *requestQ;
    pthread_mutex_t *coutMutex;
    ResultArr *resultArr;

} ThreadInfo;


Resolvers::Resolvers(int count, pthread_mutex_t &coutMutex, SafeQ<Task> &requestQue, ResultArr &resultArr): ThreadPool(count,coutMutex,&resultArr) {
    int rc;
    void *res;

    for(int i=0; i<count ; i++){
        ThreadData *tData = new ThreadData();
        tData->tid=i; //build the data and id for the thread
        tData->coutMutex=this->coutMutex;
        tData->requestQ=&requestQue;
        tData->resultArr=this->resultArr;
        this_thread::sleep_for(chrono::microseconds(1000000));
        rc=pthread_create(threads[i], NULL, resDomainName, (void*)tData);

        pthread_join(*threads[i], &res);

        //cout<<"!!!!!"<<this->resultArr->pop()->getUrl();
    }


}

//multi-threading function
void * resDomainName(void * tData) {
    ThreadData *fn= (ThreadData*)tData;          //convert the tData to struct
    char *cUrl;
    string *url=new string ("NotNull");

    while(true){
        Task *task=fn->requestQ->deQ();
        url= task->getUrl();
        while(url==NULL){           //url is null when the queue is empty
            this_thread::sleep_for(chrono::microseconds(10000));
            url= task->getUrl();
            cout<<"\n waiting for tasks...";
        }


        cUrl = new char[url->length() + 1];
        strcpy(cUrl, url->c_str());
        char** IPS=new char*[MAX_ADDRESSES];
        for(int i=0;i<MAX_ADDRESSES;i++)
            IPS[i]=new char[1024];
        int numIp;

        pthread_mutex_lock(fn->coutMutex);
        if(dnslookupAll(cUrl,IPS,MAX_ADDRESSES,&numIp)==UTIL_FAILURE){
            //do nothing !
        } else{
            //success case
            string *concatIps= new string();
            for(int i=0; i<numIp ; i++){
                string tmp(IPS[i]);
                *concatIps += tmp;
                *concatIps += ",";
            }

            task->setIp(concatIps);

            cout<<"Resolver id "<<fn->tid<<": URL: "<<*url<<" TO: ";
            for (int i=0; i<numIp; i++)
                cout<<IPS[i]<<",";
            cout<<"\n";
        }
        pthread_mutex_unlock(fn->coutMutex);

        //adding to result array
        fn->resultArr->push(new Node(task));
    }


    pthread_exit(NULL);
}


//stub function
int dns(const char* hostname,char *firstIPstr,int maxSize){
    char * tmp= "255.255.255.255";
    strcpy(firstIPstr,tmp);
    return 1;
}