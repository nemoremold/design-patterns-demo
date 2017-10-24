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

int main(void) {

    #ifdef BUSINESS_CAR
    BusinessCarFactory carFactory;
    #else
    SportsCarFactory carFactory;
    #endif

    dp::shared_ptr<AudiCar> car = carFactory.createAudiCar(std::string("AudiCar"));
    car->drive();

    Log &log = Log::Instance();
    log.addNew(std::string("Log test1"));
    log.addNew(std::string("Log test2"));
    log.showAll();

    ServicePlatformDirector director;
    director.setBuilder(std::unique_ptr<BenzServicePlatformBuilder>(new BenzServicePlatformBuilder));
    director.construct();
    director.setBuilder(std::unique_ptr<BmwServicePlatformBuilder>(new BmwServicePlatformBuilder));
    director.construct();
    director.setBuilder(std::unique_ptr<AudiServicePlatformBuilder>(new AudiServicePlatformBuilder));
    director.construct();

    std::shared_ptr<Guest> guest1(new Guest());
    guest1->setName(std::string("GUEST1"));
    auto guest2 = guest1->clone();
    std::cout << guest1->getName() << std::endl;
    guest2->setName(std::string("GUEST2"));
    std::cout << guest2->getName() << std::endl;
    std::cout << guest1->getName() << std::endl;
    
    std::shared_ptr<LargeServiceLine> largeServiceLine(new LargeServiceLine());
    std::shared_ptr<SmallServiceLine> smallServiceLine(new SmallServiceLine());
    smallServiceLine->setNext(largeServiceLine);

    for (size_t i = 1; i <= 30; ++i) {
        auto guest = guest1->clone();
        guest->setName(std::string("LINEGUEST") + std::to_string(i));
        smallServiceLine->handle(guest);
    }

    smallServiceLine->serve();

    ChatRoom chatRoom;
    std::shared_ptr<Manager> manager(new Manager());
    manager->setName(std::string("MANAGER"));

    chatRoom.addPerson(guest1);
    chatRoom.addPerson(guest2);
    chatRoom.addPerson(manager);

    guest1->setContent(std::string("Hello!"));
    manager->setContent(std::string("Welcome~"));

    chatRoom.notify(manager);

    guest2->setContent(std::string("Hey!"));
    guest1->setContent(std::string("What's up?"));

    chatRoom.chat(guest1, guest2);

    return 0;
}
