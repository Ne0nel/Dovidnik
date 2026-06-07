#pragma once
#include <string>
#include <vector>
#include <iostream>

class Phone {
    private:
        std::string category;
        std::string full_form;
        std::string medium_form;
        std::string short_form;
    public:
        Phone(std::string category, std::string full, std::string med, std::string sh)
        : category(category), full_form(full), medium_form(med), short_form(sh) {}

        std::string getCategory() const { return category; }
        std::string getFull() const { return full_form; }
        std::string getMedium() const { return medium_form; }
        std::string getShort() const { return short_form; }

        void print() const {
            std::cout << category << ": "
                      << full_form
                      << " (" << medium_form << ", "
                      << short_form << ")";
        }
};

class Record {
    protected:
        std::vector<Phone> phones;
        std::vector<std::string> emails;
    public:
        Record(std::vector<Phone> phones, std::vector<std::string> emails)
        : phones(phones), emails(emails){}

        virtual ~Record() = default;

        virtual void print() const = 0;

        const std::vector<Phone>& getPhones() const { return phones; }
        std::vector<Phone>& getPhones() { return phones; }
        const std::vector<std::string>& getEmails() const { return emails;}
        std::vector<std::string>& getEmails() { return emails; }
};

