#ifndef __CONCURRENT_DEQUE_
#define __CONCURRENT_DEQUE_

#include "list.hpp"
#include <mutex>
#include <condition_variable>
#include <iostream>

template<typename T>
class concurrent_deque {
private:
    bool is_full() const
    {
        return m_queue.size() == m_maxSize;
    }

    bool is_empty() const
    {
        return m_queue.empty();
    }

public:
    concurrent_deque(int maxSize) : m_maxSize(maxSize)
    {
    }

    void push_back(const T& x)
    {
        std::lock_guard<std::mutex> locker(m_mutex);

        while (is_full())
        {
            std::cout << "the blocking queue is full,waiting..." << std::endl;
            m_notFull.wait(m_mutex);
        }
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    void pop_front(T& x)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        
        while (is_empty())
        {
            std::cout << "the blocking queue is empty,wating..." << std::endl;
            m_notEmpty.wait(m_mutex);
        }
       
        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

private:
    dp::list<T> m_queue;                  
    std::mutex m_mutex;                    
    std::condition_variable_any m_notEmpty;
    std::condition_variable_any m_notFull;
    int m_maxSize;
};

#endif