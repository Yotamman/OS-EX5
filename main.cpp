#include <iostream>
#include "SafeQ.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SafeQ<int> q(1);
    int arry[50];
    q.enQ(arry);
    q.deQ();
    cout<<"is full:"<<q.isFull()<<"\n";
    cout<<"is empty:"<<q.isEmpty();

    return 0;
}