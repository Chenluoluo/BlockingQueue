//
// Created by 陈希 on 2018/4/7.
//

#ifndef THREADPOOL_WAITCONDITION_H
#define THREADPOOL_WAITCONDITION_H


#include <pthread.h>
#include "Mutex.h"

class Condition {
public:
    explicit Condition(Mutex& mutex);
    ~Condition();

    void wait();
    void wakeOne();
    void wakeAll();

    //nocopy
    Condition(const Condition&)=delete;
    Condition(Condition&&)=delete;
    Condition& operator=(const Condition&)=delete;
    Condition& operator=(Condition&&)=delete;

private:
    pthread_cond_t _cond;
    Mutex& _mutex;
};


#endif //THREADPOOL_WAITCONDITION_H
