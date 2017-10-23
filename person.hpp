#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include <memory>
#include <string>

class Person {
public:
    std::shared_ptr<Person> clone() {
        return std::shared_ptr<Person>(new Person(*this));
    }

    void setName(std::string s) {
        _name = s;
    }

    std::string getName() {
        return _name;
    }

private:
    std::string _name;
};

#endif
