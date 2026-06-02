#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cstdlib> 
#include <ctime>

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
            std::cout << "Головний номер: "; //как главный номер красивее записать
            switch (category) {
            case PhoneCategory::Home:   std::cout << "Домашній: "; break;
            case PhoneCategory::Mobile: std::cout << "Мобільний: "; break;
            case PhoneCategory::Work:   std::cout << "Робочий: "; break;
            }
            std::cout << full_form << " (" << short_form << ")";
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

class Person : public Record { //разделить на два файла
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

class Organization : public Record{ //разделить на два файла
    private:
        std::string title;
        std::string activity;
        Person* manager;
    public:
        Organization(std::string title, std::string activity, Person* manager, 
        std::vector<Phone> phones, std::vector<std::string> emails);
        
        void print() const override; 
        std::string getTitle() const; 
        Person* getManager() const;
        void setManager(Person* mngr);
        
};

Person::Person(std::string name, std::string gender, Organization* org, std::vector<Phone> phs, std::vector<std::string> ems)
        : Record(phs, ems), name(name), gender(gender), organization(org) {}

std::string Person::getName() const { return name; }
Organization* Person::getOrganization() const { return organization; }
void Person::setOrganization(Organization* org) { organization = org; }

void Person::print() const { //некрасиво
    std::cout << "ПІБ: " << name << "\n" << "Стать: " << gender << "\n" << "Організація: ";
    
    if (organization != nullptr) std::cout << organization->getTitle() << "\n";
    else std::cout << "немає\n";
    
    for(auto phone: phones){
        phone.print();
        std::cout << "\n";
    }
    for(auto email: emails){
        std::cout << email;
        std::cout << "\n";
    }
}

Organization::Organization(std::string title, std::string activity, Person* manager, std::vector<Phone> phs, std::vector<std::string> ems)
        : Record(phs, ems), title(title), activity(activity), manager(manager) {}

std::string Organization::getTitle() const {return title; }
Person* Organization::getManager() const {return manager;}
void Organization::setManager(Person* mngr) {manager = mngr;}

void Organization::print() const { //некрасиво
    std::cout << "Назва: " << title << "\n" << "Діяльність: " << activity << "\n" << "Керівник: ";
    
    if (manager != nullptr) std::cout << manager->getName() << "\n";
    else std::cout << "немає\n";
    
    for(auto phone: phones){
        phone.print();
        std::cout << "\n";
    }
    for (auto email : emails){
        std::cout << email;
        std::cout << "\n";
    }
}


class PhoneBook { //можно разделить на два
    private:
        std::vector<Record*> records;
    public:
        ~PhoneBook() { for (auto* record : records) delete record; }

        void addRecord(Record* record){ records.push_back(record);}
        void removeRecord(int index){ records.erase(records.begin() + index + 1);}
        const std::vector<Record*>& getRecords() const { return records; }

        std::vector<Record*> findByName(const std::string& name) const{
            std::vector<Record*> found;

            for(auto record : records){
                Person* check = dynamic_cast<Person*> (record);
                if(check != nullptr && (check->getName()).find(name) != std::string::npos){
                    found.push_back(record);
                }
            }
            return found;
        }
        std::vector<Record*> findByPhone(const std::string& phoneNumber) const{
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
        std::vector<Record*> findByEmail(const std::string& searchEmail) const {
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
};

void BookCreate(PhoneBook& book){ //либо функция либо в мейн
}

Phone generateRandomPhone() { //чотко
    std::vector<std::string> phoneCodes = {"050", "067", "093", "063"};
    std::string code = phoneCodes[rand() % phoneCodes.size()];

    std::string number = "";
    for(int i = 0; i < 7; ++i) {
        number += std::to_string(rand() % 10);
    }
        
    PhoneCategory cat = static_cast<PhoneCategory>(rand() % 3);
        
    std::string full = "+38" + code + number;
    std::string medium = "0" + code + "-" + number.substr(0,3) + "-" + number.substr(3);
    std::string shortt = number.substr(0,3) + "-" + number.substr(3);
        
    return Phone(cat, full, medium, shortt);
}

int main(){

    srand(static_cast<unsigned int>(time(nullptr))); 

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);


    std::vector<std::string> maleNames = {"Шевченко Тарас Григорович", "Сукачук Андрій Миколайович", "Ковальський Руслан Станіславович", "Політаєв Артур Дмитрович", "Маркарян Арсен Ашотович"};
    std::vector<std::string> femaleNames = {"Потім додам", "Завтра додам", "Іншим разом", "Колись пізніше", "Не сьогодні"};
    std::vector<std::string> organizations = {"Дота", "Мобла", "КС", "Апекс"};
    std::vector<std::string> activities = {"Це", "То", "Інше", "Щось"};
    std::vector<std::string> emails = {"@1", "@2", "@3", "@4", "@5"};

    PhoneBook book;
    //вот эту залупу переделать
    int Records = 5;
    for(int i = 0; i < Records; i++){
        std::string title = organizations[rand() % organizations.size()];
        std::string activity = activities[rand() % activities.size()];
        bool HasAManager = rand() % 2;

        std::vector<Phone> org_phoneNumbers = {generateRandomPhone(), generateRandomPhone(), generateRandomPhone()};
        std::vector<std::string> org_email = {emails[rand() % emails.size()]};
        
        Organization* org = new Organization(title, activity, nullptr, org_phoneNumbers, org_email);

        int randgender = rand() % 2;
        bool HasAJob = rand() % 2;
        std::string name, gender;
        if (randgender == 0){
            name = maleNames[rand() % maleNames.size()]; 
            gender = "male";
        } else {
            name = femaleNames[rand() % femaleNames.size()];
            gender = "female";
        }
        std::vector<Phone> person_phoneNumbers = {generateRandomPhone()};
        std::vector<std::string> person_email = {emails[rand() % emails.size()]};

        Person* p = new Person(name, gender, (HasAJob? org : nullptr), person_phoneNumbers, person_email );

        if(HasAManager) org->setManager(p);
        
        book.addRecord(p);
        book.addRecord(org);
    }

    for(auto* record : book.getRecords()){
        record->print();
        std::cout << "-------------------------------------------------------\n";
    }

    while(std::cin){
        std::string searchname;
        std::getline(std::cin,  searchname);
        for(auto found : book.findByName(searchname)){
            found->print();
        }
    }
}