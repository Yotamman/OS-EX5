//
// Created by Ben on 16/05/2018.
//

#include "Task.h"

Task::Task(string *ip, string *url, pthread_cond_t *cond) : ip(ip), url(url), cond(cond) {
    this->cond=cond;
    this->url=url;
    this->ip=ip;
}

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
