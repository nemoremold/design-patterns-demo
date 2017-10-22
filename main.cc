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
    BenzServicePlatformBuilder benzServicePlatformBuilder;
    director.setBuilder(&benzServicePlatformBuilder);
    director.construct();
    BmwServicePlatformBuilder bmwServicePlatformBuilder;
    director.setBuilder(&bmwServicePlatformBuilder);
    director.construct();
    AudiServicePlatformBuilder audiServicePlatformBuilder;
    director.setBuilder(&audiServicePlatformBuilder);
    director.construct();


    std::shared_ptr<Tool> spanner(new Spanner());
    std::shared_ptr<Tool> screwdriver(new Screwdriver());
    std::shared_ptr<Tool> pincher(new Pincher());
    std::shared_ptr<Tool> smallToolbox(new Toolbox());

    std::dynamic_pointer_cast<Toolbox>(smallToolbox)->add(spanner);
    std::dynamic_pointer_cast<Toolbox>(smallToolbox)->add(screwdriver);

    std::shared_ptr<Tool> largeToolbox(new Toolbox());
    std::dynamic_pointer_cast<Toolbox>(largeToolbox)->add(pincher);
    std::dynamic_pointer_cast<Toolbox>(largeToolbox)->add(smallToolbox);

    largeToolbox->exert();

    return 0;
}
