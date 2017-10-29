#ifndef _ASSISTANT_HPP_
#define _ASSISTANT_HPP_

#include "utility/shared_ptr.hpp"

#include "log.hpp"
#include "chat.hpp"
#include "person.hpp"
#include "toolbox.hpp"
#include "car_factory.hpp"
#include "service_line.hpp"
#include "service_platform.hpp"

#include <list>
#include <memory>
#include <string>
#include <thread>
#include <cstdarg>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <type_traits>

class Assistant {
public:
    void initializeServicePlatform() {
        ServicePlatformDirector director;
        director.setBuilder(std::unique_ptr<BenzServicePlatformBuilder>(new BenzServicePlatformBuilder));
        director.construct();
        director.setBuilder(std::unique_ptr<BmwServicePlatformBuilder>(new BmwServicePlatformBuilder));
        director.construct();
        director.setBuilder(std::unique_ptr<AudiServicePlatformBuilder>(new AudiServicePlatformBuilder));
        director.construct();
    }

    std::shared_ptr<Guest> initializeGuest(std::string name) {
        std::shared_ptr<Guest> guest(new Guest());
        guest->setName(name);
        return guest;
    }

    std::shared_ptr<Guest> cloneGuest(std::shared_ptr<Guest> guest, std::string name) {
        std::shared_ptr<Guest> clone_guest = guest->clone();
        clone_guest->setName(name);
        return clone_guest;
    }

    std::shared_ptr<Manager> initializeManager(std::string name) {
        std::shared_ptr<Manager> manager(new Manager());
        manager->setName(name);
        return manager;
    }

    template <typename T>
    std::shared_ptr<typename std::enable_if<std::is_base_of<ServiceLine, T>::value, T>::type> initializeServiceLine() {
        std::shared_ptr<T> serviceLine(new T());
        return serviceLine;
    }

    void log(std::string content) {
        Log *log = Log::getInstance();
        log->addNew(content);
        log->showAll();
    }

    void multiThreading(size_t count, ...) {
        va_list args;
        va_start(args, count);
        std::list<std::thread> server_list;
        while (count--) {
            size_t no = va_arg(args, size_t);
            auto serviceLine= *(va_arg(args, std::shared_ptr<ServiceLine>*));
            while (no--) {
                std::thread server(multithread_serve, serviceLine);
                server_list.push_back(std::move(server));
            }
            count--;
        }
        va_end(args);
        while (!server_list.empty()) {
            server_list.front().join();
            server_list.pop_front();
        }
    }

private:
    static void multithread_serve(std::shared_ptr<ServiceLine> serviceLine) {
        while (!serviceLine->isEmpty()) {
            serviceLine->serve();
        }
    }
};

#endif
