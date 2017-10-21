#include "utility/shared_ptr.hpp"

#include "log.hpp"
#include "car_factory.hpp"

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

    return 0;
}
