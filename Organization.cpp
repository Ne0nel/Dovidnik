#include "Organization.h"
#include "Person.h"
#include <iostream>

Organization::Organization(std::string title, std::string activity, Person* manager, std::vector<Phone> phs, std::vector<std::string> ems)
        : Record(phs, ems), title(title), activity(activity), manager(manager) {}

std::string Organization::getTitle() const  {return title; }
Person* Organization::getManager() const    {return manager;}
void Organization::setManager(Person* mngr) {manager = mngr;}

void Organization::print() const {
    std::cout << "Назва: "      << title    << "\n" 
              << "Діяльність: " << activity << "\n" 
              << "Керівник: ";

    if (manager != nullptr) std::cout << manager->getName() << "\n";
    else                    std::cout << "немає\n";

    std::cout << "Головний номер телефону: ";
    for (const auto& phone: phones){
        phone.print();
        std::cout << "\n";
    }
    std::cout << "Електронні пошти: \n";
    for (const auto& email : emails){
        std::cout << email << "\n";
    }
}
