#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include <memory>
#include <string>
#include <iostream>

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
            std::cout << "Guest " << getName() << " says: " << getContent() << std::endl;
        }
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
