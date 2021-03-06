#ifndef _CAR_FACTORY_HPP_
#define _CAR_FACTORY_HPP_

#include "utility/shared_ptr.hpp"
#include "car.hpp"

#include <string>

// Abstract factory
class CarFactory {
public:
    virtual dp::shared_ptr<BenzCar> createBenzCar(std::string carName) = 0;
    virtual dp::shared_ptr<BmwCar> createBmwCar(std::string carName) = 0;
    virtual dp::shared_ptr<AudiCar> createAudiCar(std::string carName) = 0;
};

// Concrete factories
class SportsCarFactory : public CarFactory {
public:
    dp::shared_ptr<BenzCar> createBenzCar(std::string carName) {
        auto car = dp::shared_ptr<BenzCar>(new BenzSportsCar());
        car->setName(carName);
        return car;
    }
    dp::shared_ptr<BmwCar> createBmwCar(std::string carName) {
        auto car = dp::shared_ptr<BmwCar>(new BmwSportsCar());
        car->setName(carName);
        return car;
    }
    dp::shared_ptr<AudiCar> createAudiCar(std::string carName) {
        auto car = dp::shared_ptr<AudiCar>(new AudiSportsCar());
        car->setName(carName);
        return car;
    }
};

class BusinessCarFactory : public CarFactory {
public:
    dp::shared_ptr<BenzCar> createBenzCar(std::string carName) {
        auto car = dp::shared_ptr<BenzCar>(new BenzBusinessCar());
        car->setName(carName);
        return car;
    }  
    dp::shared_ptr<BmwCar> createBmwCar(std::string carName) {
        auto car = dp::shared_ptr<BmwCar>(new BmwBusinessCar());
        car->setName(carName);
        return car;
    }
    dp::shared_ptr<AudiCar> createAudiCar(std::string carName) {
        auto car = dp::shared_ptr<AudiCar>(new AudiBusinessCar());
        car->setName(carName);
        return car;
    }
}; 

#endif
