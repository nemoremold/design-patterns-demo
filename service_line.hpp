#ifndef _SERVICE_LINE_HPP_
#define _SERVICE_LINE_HPP_

#include "person.hpp"
#include "utility/concurrent_deque.hpp"
#include <cstdio>
#include <deque>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <mutex>


class ServiceLine {
public:
    // The "chain" method in the base class
    // always delegates to the next object
    virtual void handle(std::shared_ptr<Guest> g) {
        if (_next) {
            _next->handle(g);
        }
        else {
            std::lock_guard<std::mutex> locker(mutex);
            
            std::cout << "ServiceLine is full!" << std::endl;
        }
    }

    void setNext(std::shared_ptr<ServiceLine> next) {
        _next = next;
    }

    bool isFull(size_t size) {
        return _queue.size() >= size;
    }

    bool isEmpty() {
        return _queue.empty();
    }

    std::shared_ptr<Guest> serve() {
        auto g = _queue.front();
        std::lock_guard<std::mutex> locker(mutex);
        
        std::cout << "Guest " << g->getName() << " is now to get service." << std::endl;
        
        _queue.pop_front();
        notify();
        return g;
    }

    void addToQueue(std::shared_ptr<Guest> g) {
        _queue.push_back(g);
    }

    void notify() {
        std::for_each(_queue.begin(), _queue.end(), [](std::shared_ptr<Guest> &p){ p->update(); });
    }

private:
    // "next" pointer in the base class
    std::shared_ptr<ServiceLine> _next;

    dp::concurrent_deque<std::shared_ptr<Guest>> _queue;

    // concurrent_deque<std::shared_ptr<Guest>> _queue;
};

class LargeServiceLine : public ServiceLine {
public:
    void handle(std::shared_ptr<Guest> g) override {
        if (isFull(20)) {
            ServiceLine::handle(g);
        }
        else {
            std::lock_guard<std::mutex> locker(mutex);
            
            std::cout << "Guest " << g->getName() << " gets handled in LargeServiceLine..." << std::endl;
            
            addToQueue(g);
        }
    }
};

class SmallServiceLine : public ServiceLine {
public:
    void handle(std::shared_ptr<Guest> g) override {
        if (isFull(5)) {
            ServiceLine::handle(g);
        }
        else {
            std::lock_guard<std::mutex> locker(mutex);
            
            std::cout << "Guest " << g->getName() << " gets handled in SmallServiceLine..." << std::endl;
            
            addToQueue(g);
        }
    }
};

#endif
