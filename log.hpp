#ifndef _LOG_HPP_
#define _LOG_HPP_

#include "utility/vector.hpp"

#include <mutex>
#include <atomic>
#include <string>
#include <iostream>

class Log {
public:
    static Log* getInstance() {
        Log *tmp = log.load(std::memory_order_acquire);  // low-level acquire/release operation
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);

            // Maybe many threads are locked here by the mutex at the same time.
            // After the lock is free (the singleton is created by one thread), load again.
            tmp = log.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new Log;
                log.store(tmp, std::memory_order_release); // low-level acquire/release operation
            }
        }
        return tmp;
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
    static std::atomic<Log *> log;
    static std::mutex mutex;

protected:
    Log() { }
    ~Log() { }
};

std::atomic<Log*> Log::log;
std::mutex Log::mutex;

#endif
