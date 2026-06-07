#pragma once
#include "Record.h"
#include <string>

class Organization;

class Person : public Record {
    private:
        std::string name;
        std::string gender;
        Organization* organization;
    public:
        Person(std::string name, std::string gender, Organization* org, std::vector<Phone> phs, std::vector<std::string> ems);

        void print() const override;

        std::string getName() const;
        Organization* getOrganization() const;
        void setOrganization(Organization* org);
        void setName(const std::string& newName);
        void setGender(const std::string& newGender);
};

