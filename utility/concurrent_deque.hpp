#ifndef _CONCURRENT_DEQUE_HPP_
#define _CONCURRENT_DEQUE_HPP_

#include "list.hpp"
#include <mutex>
#include <condition_variable>
#include <iostream>

namespace dp {

template<typename T>
class concurrent_deque {
private:
    bool inner_empty() {
        return m_queue.empty();
    }

public:
    concurrent_deque(){}

    bool empty() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    void push_back(const T& x) {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_queue.push_back(x);
    }

    T& front() {
        std::lock_guard<std::mutex> locker(m_mutex);        
        return m_queue.front();
    }

    size_t size() {
        std::lock_guard<std::mutex> locker(m_mutex);        
        return m_queue.size();
    }

    auto begin() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.begin();
    }

    auto end() {
        std::lock_guard<std::mutex> locker(m_mutex);   
        return m_queue.end();
    }

    void pop_front() {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_queue.pop_front();
    }

private:
    dp::list<T> m_queue;                  
    std::mutex m_mutex;                    
    std::condition_variable_any m_notEmpty;
    std::condition_variable_any m_notFull;
};

}

#endif
