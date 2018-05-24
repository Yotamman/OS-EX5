//
// Created by Ben on 16/05/2018.
//

#include "Task.h"


string *Task::getIp() const {
    return ip;
}

void Task::setIp(string *ip) {
    Task::ip = ip;
}

string *Task::getUrl() const {
    return url;
}

void Task::setUrl(string *url) {
    Task::url = url;
}

pthread_cond_t *Task::getCond() const {
    return cond;
}

void Task::setCond(pthread_cond_t *cond) {
    Task::cond = cond;
}

Task::Task(string *ip, string *url, pthread_cond_t *cond, pthread_mutex_t *condMutex) {
    this->cond=cond;
    this->url=url;
    this->ip=ip;
    this->condMutex=condMutex;
}


