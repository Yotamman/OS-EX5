#include <iostream>
#include "SafeQ.h"
#include "Task.h"
#include "Requesters.h"
#include <sstream>
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "Resolvers.h"
#include "ResultArr.h"
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <condition_variable>
//extern "C"
//{
//#include "util.h"
//}



using namespace std;

int finishFlag=0;

//int argc, char *argv[]
int main() {
    srand(time(NULL));

    int argc=1;
    char *argv[1];
    int qSize = 10;
    argv[0]="names1.txt";
    //argv[1]="names2.txt";


    pthread_mutex_t coutMutex = PTHREAD_MUTEX_INITIALIZER;

    ResultArr *resultArr=new ResultArr(&coutMutex);
    SafeQ<Task> *requestQ=new SafeQ<Task>(qSize);

    Requesters reqs(argv,argc,coutMutex,*requestQ,*resultArr);
    Resolvers resolvers(argc,coutMutex,*requestQ,*resultArr);

    while(true){}


    // in the end we need to wait for all resolver to finsih thier work.
    return 0;
}