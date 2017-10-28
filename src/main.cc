#include "utility/shared_ptr.hpp"

#include "log.hpp"
#include "chat.hpp"
#include "person.hpp"
#include "toolbox.hpp"
#include "assistant.hpp"
#include "car_factory.hpp"
#include "service_line.hpp"
#include "service_platform.hpp"

#include <memory>
#include <string>
#include <thread>
#include <iostream>

int main(void) {

    #ifdef BUSINESS_CAR
    BusinessCarFactory carFactory;
    #else
    SportsCarFactory carFactory;
    #endif

    auto assistant = Assistant();

    dp::shared_ptr<AudiCar> car = carFactory.createAudiCar(std::string("AudiCar"));
    car->drive();

    assistant.log("Log test");

    assistant.initializeServicePlatform();

    auto guest1 = assistant.initializeGuest("GUEST1");
    auto guest2 = assistant.cloneGuest(guest1, "GUEST2");
    std::cout << guest1->getName() << std::endl;
    std::cout << guest2->getName() << std::endl;

    auto largeServiceLine = assistant.initializeServiceLine<LargeServiceLine>();
    auto smallServiceLine = assistant.initializeServiceLine<SmallServiceLine>();
    smallServiceLine->setNext(largeServiceLine);

    for (size_t i = 1; i <= 30; ++i) {
        auto guest = guest1->clone();
        guest->setName(std::string("LINEGUEST") + std::to_string(i));
        smallServiceLine->handle(guest);
    }

    assistant.multiThreading(4, 2, &smallServiceLine, 2, &largeServiceLine);

    ChatRoom chatRoom;
    auto manager = assistant.initializeManager("MANAGER");

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
