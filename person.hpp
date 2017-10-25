#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include <memory>
#include <string>
#include <iostream>

static std::mutex mutex;
class Person {
public:
    void setName(std::string s) {
        _name = s;
    }

    std::string getName() {
        return _name;
    }

    void setContent(std::string s) {
        _content = s;
    }

    std::string getContent() {
        return _content;
    }

    virtual void talk() = 0;

private:
    std::string _name;
    std::string _content;
};

class Guest : public Person {
public:
    std::shared_ptr<Guest> clone() {
        return std::shared_ptr<Guest>(new Guest(*this));
    }

    void talk() override {
        if (!getContent().empty()) {
            std::lock_guard<std::mutex> locker(mutex);
            
            std::cout << "Guest " << getName() << " says: " << getContent() << std::endl;
        }
    }

    void update() {
        std::cout << "Guest " << getName() << " received notification." << std::endl;
    }
};

class Manager : public Person {
public:
    void talk() override {
        if (!getContent().empty()) {
            std::cout << "Manager " << getName() << " says: " << getContent() << std::endl;
        }
    }
};

#endif
