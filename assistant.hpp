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

#include <memory>
#include <string>
#include <iostream>
#include <type_traits>
#include <stdexcept>

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

    template <typename T>
    std::shared_ptr<typename std::enable_if<std::is_base_of<ServiceLine, T>::value, T>::type> initializeServiceLine() {
        std::shared_ptr<T> serviceLine(new T());
        return serviceLine;
    }

    void log(std::string content) {
        Log &log = Log::Instance();
        log.addNew(content);
        log.showAll();
    }
};

#endif
