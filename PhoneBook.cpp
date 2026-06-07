#include "PhoneBook.h"
#include "Person.h"
#include "Organization.h"
#include <algorithm>

PhoneBook::~PhoneBook() { for (auto* record : records) delete record; }

void PhoneBook::addRecord(Record* record){ records.push_back(record);}
void PhoneBook::removeRecord(int index){ 
     if (index < 0 || index >= static_cast<int>(records.size())) {
        return;
    }

    Record* record = records[index];

    if (auto* org = dynamic_cast<Organization*>(record)) {
        for (auto* rec : records) {
            if (auto* person = dynamic_cast<Person*>(rec)) {
                if (person->getOrganization() == org) {
                    person->setOrganization(nullptr);
                }
            }
        }
    } else if (auto* person = dynamic_cast<Person*>(record)) {
        for (auto* rec : records) {
            if (auto* org = dynamic_cast<Organization*>(rec)) {
                if (org->getManager() == person) {
                    org->setManager(nullptr);
                }
            }
        }
    }

    records.erase(records.begin() + index);
    delete record;
}

std::vector<Record*> PhoneBook::findByName(const std::string& name) const{
    std::vector<Record*> found;
    for(auto record : records){
        Person* check = dynamic_cast<Person*> (record);
        if(check != nullptr && (check->getName()).find(name) != std::string::npos){
            found.push_back(record);
        }
    }
    return found;
}

std::vector<Record*> PhoneBook::findByPhone(const std::string& phoneNumber) const{
    std::vector<Record*> found;
    for(auto record : records){
        for (auto phone : record->getPhones()){
            if(phoneNumber == phone.getFull() || phoneNumber ==  phone.getMedium() || phoneNumber ==  phone.getShort()){
                found.push_back(record);
                break;
            }
        }
    }
    return found;
}

std::vector<Record*> PhoneBook::findByEmail(const std::string& searchEmail) const {
    std::vector<Record*> found;
    for (auto record : records){
        for(auto email : record->getEmails()){
            if (email == searchEmail){
                found.push_back(record);
                break;
            }
        }
    }
    return found;
}
