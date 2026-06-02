#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <windows.h>

class Organization;
class Person;

enum class PhoneCategory {Home, Mobile, Work};

class Phone {
    private:
        PhoneCategory category;
        std::string full_form;
        std::string medium_form;
        std::string short_form;
    public:
        Phone (PhoneCategory category, std::string full, std::string med, std::string sh) :
        category(category), full_form(full), medium_form(med), short_form(sh) {}

        PhoneCategory getCategory() const { return category; }
        std::string getFull() const { return full_form; }
        std::string getMedium() const { return medium_form; }
        std::string getShort() const { return short_form; }

        void print(){
            switch (category) {
            case PhoneCategory::Home:   std::cout << "Домашній: "; break;
            case PhoneCategory::Mobile: std::cout << "Мобільний: "; break;
            case PhoneCategory::Work:   std::cout << "Робочий: "; break;
            }
            std::cout << full_form << " (або " << short_form << ")" << std::endl;
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
        const std::vector<std::string>& getEmails() const { return emails;}
};

class Person : public Record {
    private:
        std::string name;
        std::string gender; 
        Organization* organization;
    public:
        Person(std::string name, std::string gender, Organization* org, 
        std::vector<Phone> phs, std::vector<std::string> ems);

        void print() const override;

        std::string getName() const;
        Organization* getOrganization() const;
        void setOrganization(Organization* org);
};

class Organization : public Record{
    private:
        std::string title;
        std::string activity;
        Person* manager;
    public:
        Organization(std::string title, std::string activity, Person* manager, 
        std::vector<Phone> phones, std::vector<std::string> emails);
        
        void print() const override; 
        std::string getTitle() const; 
        
};

Person::Person(std::string name, std::string gender, Organization* org, std::vector<Phone> phs, std::vector<std::string> ems)
        : Record(phs, ems), name(name), gender(gender), organization(org) {}

std::string Person::getName() const { return name; }
Organization* Person::getOrganization() const { return organization; }
void Person::setOrganization(Organization* org) { organization = org; }

void Person::print() const {
    std::cout << "ПІБ: " << name << "\n" << "Стать: " << gender << "\n" << "Організація: ";
    
    if (organization != nullptr) std::cout << organization << "\n";
    else std::cout << "немає\n";
    
    for(auto phone: phones){
        phone.print();
        std::cout << "\n";
    }
    std::cout << "-----------------------------------------" << std::endl;
}


class PhoneBook {

};

int main(){

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::string name = "Arsen Markaryan", gender = "GENDER", org = "ORG";
    std::string f = "+380956184047", m = "0956184047", s = "095-618-4047";
    Phone phone (PhoneCategory(0), f, m, s);
    std::vector<Phone> phs = {phone};
    std::string em = "feffe@fgff";
    std::vector<std::string> ems = {em};
    Person test(name, gender, nullptr, phs, ems);

    test.print();
    test.print();
}