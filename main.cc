#include "utility/shared_ptr.hpp"

#include "log.hpp"
#include "toolbox.hpp"
#include "car_factory.hpp"
#include "service_platform.hpp"

#include <memory>
#include <string>
#include <iostream>

int main(void) {

    dp::shared_ptr<int> a(new int(22));
    std::cout << *a << std::endl;
    if (true) {
        dp::shared_ptr<int> myPtr(new int(24));
        std::cout << *myPtr << std::endl;
        a = myPtr;
        std::cout << *a << std::endl;
    }
    std::cout << *a << std::endl;

    #ifdef BUSINESS_CAR
    BusinessCarFactory carFactory;
    #else
    SportsCarFactory carFactory;
    #endif

    dp::shared_ptr<AudiCar> car = carFactory.createAudiCar(std::string("testcar"));
    car->drive();

    Log &log = Log::Instance();
    log.addNew(std::string("test1"));
    log.addNew(std::string("test2"));
    log.showAll();

    ServicePlatformDirector director;
    director.setBuilder(std::unique_ptr<BenzServicePlatformBuilder>(new BenzServicePlatformBuilder));
    director.construct();
    BmwServicePlatformBuilder bmwServicePlatformBuilder;
    director.setBuilder(std::unique_ptr<BmwServicePlatformBuilder>(new BmwServicePlatformBuilder));
    director.construct();
    director.setBuilder(std::unique_ptr<AudiServicePlatformBuilder>(new AudiServicePlatformBuilder));
    director.construct();

    return 0;
}
