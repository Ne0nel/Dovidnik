#include "Person.h"
#include "Organization.h"
#include <iostream>

Person::Person(std::string name, std::string gender, Organization* org, std::vector<Phone> phs, std::vector<std::string> ems)
        : Record(phs, ems), name(name), gender(gender), organization(org) {}

std::string Person::getName() const             { return name; }
Organization* Person::getOrganization() const   { return organization; }
void Person::setOrganization(Organization* org) { organization = org; }
void Person::setName(const std::string& newName) { name = newName; }
void Person::setGender(const std::string& newGender) { gender = newGender; }

void Person::print() const {
    std::cout << "ПІБ: " << name << "\n" 
              << "Стать: " << gender << "\n" 
              << "Організація: ";
              
    if (organization != nullptr) std::cout << organization->getTitle() << "\n";
    else                         std::cout << "немає\n";

    std::cout << "Головний номер телефону: ";
    for(const auto& phone: phones){
        phone.print();
        std::cout << "\n";
    }
    std::cout << "Електронні пошти: \n";
    for(const auto& email: emails){
        std::cout << email << "\n";
    }
}
