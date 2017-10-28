#ifndef _LOG_HPP_
#define _LOG_HPP_

#include "utility/vector.hpp"

#include <string>
#include <iostream>

class Log {
public:
    static Log& Instance() {
        // Since it's a static variable, if the class has already been created,
        // It won't be created again. And it is thread-safe in C++11.

        static Log log;

        // Return a reference to the instance.
        return log;
    }

    // Delete copy and move ctors and assign operators
    Log(Log const&) = delete;               // Copy ctor
    Log(Log &&) = delete;                   // Move ctor
    Log& operator=(Log const&) = delete;    // Copy assign
    Log& operator=(Log &&) = delete;        // Move assign

    void addNew(std::string s) {
        logs.push_back(s);
    }

    void showAll() {
        for (auto it = logs.begin(); it != logs.end(); ++it) {
            std::cout << *it << std::endl;
        }
    }

private:
    dp::vector<std::string> logs;

protected:
    Log() { }
    ~Log() { }
};

#endif
