//
// Created by Ben on 16/05/2018.
//

#ifndef OSHW5_TASK_H
#define OSHW5_TASK_H


#include <sys/param.h>
#include <string>
using namespace std;

class Task {

private:
    string *ip;
    string *url;
    pthread_cond_t * cond;
public:
    string *getIp() const;

    void setIp(string *ip);

    string *getUrl() const;

    void setUrl(string *url);

    pthread_cond_t *getCond() const;

    void setCond(pthread_cond_t *cond);

public:
    Task(string *ip, string *url, pthread_cond_t *cond);

};


#endif //OSHW5_TASK_H
