//
// Created by 陈希 on 2018/4/7.
//

#ifndef THREADPOOL_THREAD_H
#define THREADPOOL_THREAD_H

#include <pthread.h>
#include <functional>
#include <assert.h>



class ThreadFunction{
public:
    explicit ThreadFunction(const std::function<void()> function):_function(function){}
    ~ThreadFunction(){}
    void run(){_function();}

private:
    std::function<void()> _function;
};



class Thread {
public:
    explicit Thread(const std::function<void()> &function);
    ~Thread();

    int run();
    int join();
    bool isSTART();
    bool _isJOINED();
    pthread_t getThread();

private:

    pthread_t _thread;
    bool _START;
    bool _JOINED;
    ThreadFunction* _threadFunction;
};


#endif //THREADPOOL_THREAD_H
