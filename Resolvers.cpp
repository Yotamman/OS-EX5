//
// Created by Ben on 21/05/2018.
//

#include "Resolvers.h"

Resolvers::Resolvers(int count, pthread_mutex_t &coutMutex, SafeQ<string> &requestQue): ThreadPool(count,coutMutex) {
    

}
