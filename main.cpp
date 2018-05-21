#include <iostream>
#include "SafeQ.h"
#include "Task.h"
#include "Requesters.h"
#include <sstream>
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "Resolvers.h"
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
extern "C"
{
#include "util.h"
}



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


//    Requesters reqs(argv,argc,coutMutex,*requestQ);
//    Resolvers resolvers(argc,coutMutex,*requestQ);

    char ipstr[1024];
    const char* hostname = "www.ynet.co.il";

    if(dnslookup(hostname, ipstr, sizeof(ipstr)) == UTIL_FAILURE)
    {
        cout<<"Error"<<endl;
    }
    else
    {
        cout<<ipstr<<endl;
    }










    return 0;
}