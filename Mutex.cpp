//
// Created by 陈希 on 2018/4/7.
//


#include "Mutex.h"
#include <iostream>
Mutex::Mutex() {
    int ret = pthread_mutex_init(&_mutex, NULL);
    assert(!ret);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&_mutex);
}

void Mutex::lock() {
    pthread_mutex_lock(&_mutex);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t *Mutex::mutex() {
    return &_mutex;
}