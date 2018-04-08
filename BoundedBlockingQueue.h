//
// Created by 陈希 on 2018/4/8.
//

#ifndef BLOCKINGQUEUE_BOUNDEDBLOCKINGQUEUE_H
#define BLOCKINGQUEUE_BOUNDEDBLOCKINGQUEUE_H

#include <boost/circular_buffer.hpp>
#include "Mutex.h"
#include "Condition.h"

template <typename T>
class BoundedBlockingQueue {

public:
    explicit BoundedBlockingQueue(int maxSize):
        _mutex(),_notEmpty(_mutex),_notFull(_mutex),_queue(maxSize)
    {

    }
    ~BoundedBlockingQueue() = default;

    //放入任务
    void put(const T& t)
    {
        _mutex.lock();
        while (_queue.full())
        {
            _notFull.wait();
        }
        assert(!_queue.full());
        _queue.push_back(t);
        _notEmpty.wakeOne();
        _mutex.unlock();
    }

    //取出任务
    T take()
    {
        _mutex.lock();
        while (_queue.empty())
        {
            _notEmpty.wait();
        }
        assert(!_queue.empty());
        T t(_queue.front());
        _queue.pop_front();
        _notFull.wakeOne();
        _mutex.unlock();
        return t;
    }

    //判空
    bool empty()
    {
        _mutex.lock();
        bool empty = _queue.empty();
        _mutex.unlock();
        return empty;
    }

    //判满
    bool full()
    {
        _mutex.lock();
        bool full = _queue.full();
        _mutex.unlock();
        return full;
    }

    //当前队列的大小
    size_t size()
    {
        _mutex.lock();
        size_t size = _queue.size();
        _mutex.unlock();
        return size;
    }

    //
    size_t capacity()
    {
        _mutex.lock();
        size_t capacity = _queue.capacity();
        _mutex.unlock();
        return capacity;
    }

private:
    Mutex _mutex;
    Condition _notEmpty;
    Condition _notFull;
    boost::circular_buffer<T> _queue;
};


#endif //BLOCKINGQUEUE_BOUNDEDBLOCKINGQUEUE_H
