#include "utility/shared_ptr.hpp"
#include "car_factory.hpp"

#include <string>
#include <iostream>

int main(void) {
    shared_ptr<int> a(new int(22));
    if (true) {
        shared_ptr<int> myPtr(new int(24));
        a = myPtr;
    }

    #ifdef BUSINESS_CAR
    BusinessCarFactory carFactory;
    #else
    SportsCarFactory carFactory;
    #endif

    shared_ptr<AudiCar> car = carFactory.createAudiCar(std::string("testcar"));
    car->drive();

    return 0;
}
