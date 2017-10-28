#ifndef _CAR_HPP_
#define _CAR_HPP_

#include <string>
#include <iostream>

class Car {
private:
    std::string _name;

public:
    std::string getName() {
        return _name;
    }
    void setName(std::string name) {
        _name = name;
    }
};

class BenzCar : public Car {
public:
    virtual void drive() = 0;
};

class BmwCar : public Car {
public:
    virtual void drive() = 0;
};

class AudiCar : public Car {
public:
    virtual void drive() = 0;
};

class BenzSportsCar : public BenzCar {
    void drive() {
        std::cout << this->getName()
            << " (BenzSportsCar) drive..." << std::endl;
    }
};

class BenzBusinessCar : public BenzCar {
    void drive() {
        std::cout << this->getName()
            << " (BenzBusinessCar) drive..." << std::endl;
    }
};

class BmwSportsCar : public BmwCar {
    void drive() {
        std::cout << this->getName()
            << " (BmwSportsCar) drive..." << std::endl;
    }
};

class BmwBusinessCar : public BmwCar {
    void drive() {
        std::cout << this->getName()
            << " (BmwBusinessCar) drive..." << std::endl;
    }
};

class AudiSportsCar : public AudiCar {
    void drive() {
        std::cout << this->getName()
            << " (AudiSportsCar) drive..." << std::endl;
    }
};

class AudiBusinessCar : public AudiCar {
    void drive() {
        std::cout << this->getName()
            << " (AudiBusinessCar) drive..." << std::endl;
    }
};

#endif
