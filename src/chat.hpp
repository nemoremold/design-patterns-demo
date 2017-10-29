#ifndef _CHAT_HPP_
#define _CHAT_HPP_

#include "utility/vector.hpp"
#include "person.hpp"

#include <memory>
#include <iostream>

class Mediator {
public:
    void addPerson(std::shared_ptr<Person> p)
    {
        _list.push_back(p);
    }
    virtual void notify(std::shared_ptr<Person> p) = 0;
    virtual void chat(std::shared_ptr<Person> person1, std::shared_ptr<Person> person2) = 0;

protected:
    dp::vector<std::shared_ptr<Person>> _list;
};

class ChatRoom : public Mediator {
public:
    void notify(std::shared_ptr<Person> p) override {
        std::cout << "Notification from " << p->getName() << ":" << std::endl;
        p->talk();
        for (auto it = _list.begin(); it != _list.end(); ++it) {
            if (*it != p) {
                (*it)->talk();
            }
        }
    }

    void chat(std::shared_ptr<Person> p1, std::shared_ptr<Person> p2) override {
        std::cout << "Private chat between "
            << p1->getName() << " and " << p2->getName() << ":" << std::endl;
        p1->talk();
        p2->talk();
    }
};

#endif
