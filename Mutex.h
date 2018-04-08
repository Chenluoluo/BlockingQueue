//
// Created by 陈希 on 2018/4/7.
//

#ifndef THREADPOOL_MUTEX_H
#define THREADPOOL_MUTEX_H


#include <pthread.h>
#include <assert.h>

class Mutex {
public:
    explicit Mutex();
    ~Mutex();

    void lock();
    void unlock();
    pthread_mutex_t* mutex();

    Mutex(const Mutex&) = delete;
    Mutex(Mutex&&) = delete;
    Mutex&operator=(const Mutex&) = delete;
    Mutex&operator=(Mutex&&) = delete;

private:
    pthread_mutex_t _mutex;
};


#endif //THREADPOOL_MUTEX_H
