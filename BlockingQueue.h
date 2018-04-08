//
// Created by 陈希 on 2018/4/8.
//

#ifndef BLOCKINGQUEUE_BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_BLOCKINGQUEUE_H

#include <deque>
#include <assert.h>
#include "Mutex.h"
#include "Condition.h"

template <typename T>
class BlockingQueue {
public:
    explicit BlockingQueue():
            _mutex(),_condition(_mutex),_queue()
    {

    }
    ~BlockingQueue() = default;

    //放入任务
    void put(const T& t)
    {
        _mutex.lock();
        _queue.push_back(std::move(t));
        _condition.wakeOne();
        _mutex.unlock();
    }
    //取出任务
    T take()
    {
        _mutex.lock();
        while (_queue.empty())
        {
            _condition.wait();
        }
        assert(!_queue.empty());
        T front(std::move(_queue.front()));
        _queue.pop_front();
        _mutex.unlock();
        return front;
    }
    //当前任务队列大小
    size_t size()
    {
        _mutex.lock();
        size_t size = _queue.size();
        return size;
    }

    BlockingQueue(const BlockingQueue& other) = delete;
    BlockingQueue operator=(const BlockingQueue& other) = delete;

private:
    Mutex _mutex;
    Condition _condition;
    std::deque<T> _queue;
};



#endif //BLOCKINGQUEUE_BLOCKINGQUEUE_H
