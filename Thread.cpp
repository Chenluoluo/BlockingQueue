//
// Created by 陈希 on 2018/4/7.
//

#include "Thread.h"

Thread::Thread(const std::function<void()> &function):
        _threadFunction(new ThreadFunction(function)),_thread(0),_START(false),_JOINED(false)
{

}

Thread::~Thread() {
    if(_START && !_JOINED)
        pthread_detach(_thread);
    if (_threadFunction){
        delete _threadFunction;
        _threadFunction = nullptr;
    }
}

void* startThread(void* arg){
    ThreadFunction* threadFunction = (ThreadFunction*) arg;
    threadFunction->run();
}

int Thread::run() {
    assert(!_START);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int ret = pthread_create(&_thread, &attr, startThread, (void*)_threadFunction);
    if (ret == 0){
        _START = true;
        return 1;
    } else {
        return 0;
    }
}

int Thread::join() {
    assert(_START);
    assert(!_JOINED);
    int ret = pthread_join(_thread,NULL);
    return ret;
}

pthread_t Thread::getThread() {
    return _thread;
}

bool Thread::isSTART() {
    return _START;
}

bool Thread::_isJOINED() {
    return _JOINED;
}


