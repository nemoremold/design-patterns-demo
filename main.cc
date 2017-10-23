#include "utility/shared_ptr.hpp"

#include "log.hpp"
#include "person.hpp"
#include "toolbox.hpp"
#include "car_factory.hpp"
#include "service_line.hpp"
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

    std::shared_ptr<Person> person1(new Person());
    person1->setName(std::string("GUEST1"));
    std::shared_ptr<Person> person2 = person1->clone();
    std::cout << person1->getName() << std::endl;
    person2->setName(std::string("GUEST2"));
    std::cout << person2->getName() << std::endl;
    std::cout << person1->getName() << std::endl;
    
    std::shared_ptr<LargeServiceLine> largeServiceLine(new LargeServiceLine());
    std::shared_ptr<SmallServiceLine> smallServiceLine(new SmallServiceLine());
    smallServiceLine->setNext(largeServiceLine);

    for (size_t i = 0; i < 30; ++i) {
        auto person = person1->clone();
        smallServiceLine->handle(*person);
    }

    return 0;
}
