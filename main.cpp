#include <iostream>
#include "SafeQ.h"
#include "Task.h"
#include "Requesters.h"
#include <sstream>
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>



using namespace std;

void* foo(void* a){
    cout<< a;
}


//int argc, char *argv[]
int main() {
    srand(time(NULL));
    int argc=1;
    char *argv[1];
    int qSize = 10;
    argv[0]="names1.txt";
    pthread_mutex_t coutMutex = PTHREAD_MUTEX_INITIALIZER;


    SafeQ<string> *requestQ=new SafeQ<string>(qSize);


    Requesters reqs(argv,argc,coutMutex,*requestQ);

    pthread_t threads;








    return 0;
}