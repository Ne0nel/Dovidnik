#pragma once
#include "Record.h"
#include <string>

class Person;

class Organization : public Record{
    private:
        std::string title;
        std::string activity;
        Person* manager;
    public:
        Organization(std::string title, std::string activity, Person* manager, std::vector<Phone> phones, std::vector<std::string> emails);
        
        void print() const override; 
        std::string getTitle() const; 
        Person* getManager() const;
        void setManager(Person* mngr);
        void setTitle(const std::string& newTitle);
        void setActivity(const std::string& newActivity);
};

