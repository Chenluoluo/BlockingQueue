//
// Created by 陈希 on 2018/4/7.
//

#include "Condition.h"

Condition::Condition(Mutex& mutex):
    _mutex(mutex)
{
    pthread_cond_init(&_cond, NULL);
}

Condition::~Condition() {
    pthread_cond_destroy(&_cond);
}

void Condition::wait() {
    pthread_cond_wait(&_cond,_mutex.mutex());
}

void Condition::wakeOne() {
    pthread_cond_signal(&_cond);
}

void Condition::wakeAll() {
    pthread_cond_broadcast(&_cond);
}
