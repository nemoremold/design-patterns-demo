#ifndef _SERVICE_LINE_HPP_
#define _SERVICE_LINE_HPP_

#include "person.hpp"

#include <queue>
#include <memory>
#include <string>
#include <iostream>

class ServiceLine {
public:
    // The "chain" method in the base class
    // always delegates to the next object
    virtual void handle(Person p) {
        _next->handle(p);
    }

    void setNext(std::shared_ptr<ServiceLine> next) {
        _next = next;
    }

    bool isFull(size_t size) {
        return _queue.size() >= size;
    }

    Person serve() {
        auto s = _queue.front();
        _queue.pop();
        return s;
    }

    void addToQueue(Person p) {
        _queue.push(p);
    }

private:
    // "next" pointer in the base class
    std::shared_ptr<ServiceLine> _next;

    std::queue<Person> _queue;
};

class LargeServiceLine : public ServiceLine {
public:
    void handle(Person p) override {
        if (isFull(20)) {
            ServiceLine::handle(p);
        }
        else {
            std::cout << "Handled in LargeServiceLine" << std::endl;
            addToQueue(p);
        }
    }
};

class SmallServiceLine : public ServiceLine {
public:
    void handle(Person p) override {
        if (isFull(5)) {
            ServiceLine::handle(p);
        }
        else {
            std::cout << "Handled in SmallServiceLine" << std::endl;
            addToQueue(p);
        }
    }
};

#endif
