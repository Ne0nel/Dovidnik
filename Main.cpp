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
    
    std::cout << "Головний номер телефону: ";
    for(auto phone: phones){
        phone.print();
        std::cout << "\n";
    }
    std::cout << "Електронні пошти: \n";
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
    
    std::cout << "Головний номер телефону: ";
    for(auto phone: phones){
        phone.print();
        std::cout << "\n";
    }
    std::cout << "Електронні пошти: \n";
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

// forward declaration
Phone generateRandomPhone();

void BookCreate(PhoneBook& book){ //либо функция либо в мейн
    std::vector<std::string> maleNames = {"Шевченко Тарас Григорович", "Сукачук Андрій Миколайович", "Ковальський Руслан Станіславович", "Політаєв Артур Дмитрович", "Маркарян Арсен Ашотович"};
    std::vector<std::string> femaleNames = {"Потім додам", "Завтра додам", "Іншим разом", "Колись пізніше", "Не сьогодні"};
    std::vector<std::string> organizations = {"Дота", "Мобла", "КС", "Апекс"};
    std::vector<std::string> activities = {"Це", "То", "Інше", "Щось"};

    std::vector<Person*> persons;
    std::vector<Organization*> orgs;

    for (int i = 0; i < 10; ++i) {
        int phonesCount = rand() % 4 + 1; // 1..4
        int emailsCount = rand() % 4 + 1; // 1..4

        std::vector<Phone> phones;
        for (int p = 0; p < phonesCount; ++p) phones.push_back(generateRandomPhone());

        std::vector<std::string> emails;
        for (int e = 0; e < emailsCount; ++e) emails.push_back("user" + std::to_string(i) + "_" + std::to_string(e) + "@example.com");

        if (rand() % 2 == 0) {
            // create organization
            std::string title = organizations[rand() % organizations.size()];
            std::string activity = activities[rand() % activities.size()];
            Organization* org = new Organization(title, activity, nullptr, phones, emails);
            orgs.push_back(org);
            book.addRecord(org);
        } else {
            // create person
            int genderRand = rand() % 2;
            std::string name = (genderRand == 0) ? maleNames[rand() % maleNames.size()] : femaleNames[rand() % femaleNames.size()];
            std::string gender = (genderRand == 0) ? "male" : "female";
            Person* pptr = new Person(name, gender, nullptr, phones, emails);
            persons.push_back(pptr);
            book.addRecord(pptr);
        }
    }

    // Link persons to organizations randomly
    for (Person* p : persons) {
        if (!orgs.empty() && (rand() % 2 == 0)) {
            Organization* org = orgs[rand() % orgs.size()];
            p->setOrganization(org);
        }
    }

    // Assign managers randomly
    for (Organization* org : orgs) {
        if (!persons.empty() && (rand() % 2 == 0)) {
            Person* m = persons[rand() % persons.size()];
            org->setManager(m);
            m->setOrganization(org);
        }
    }
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

std::vector<std::string> promptEmails() {
    std::vector<std::string> res;
    while (true) {
        std::cout << "Введіть email:";
        std::string e;
        std::getline(std::cin, e);
        if (e.empty()) break;
        res.push_back(e);
    }
    return res;
}

PhoneCategory choosePhoneCategory() {
    while (true) {
        std::cout << "Оберіть категорію номера:\n1. Домашній\n2. Мобільний\n3. Робочий\n";
        int opt;
        if (!(std::cin >> opt)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore();
        switch (opt) {
            case 1: return PhoneCategory::Home;
            case 2: return PhoneCategory::Mobile;
            case 3: return PhoneCategory::Work;
            default: std::cout << "Невірний вибір, спробуйте ще.\n";
        }
    }
}

std::vector<Phone> promptPhones() {
    std::vector<Phone> res;
    while (true) {
        std::cout << "Введіть номер телефону (формат +380XXYYYYYYY):";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) break;
        PhoneCategory cat = choosePhoneCategory();
        std::string digits = line.substr(1);
        std::string shortf = digits.substr(digits.size() - 4) + '-' + digits.substr(digits.size() - 7, 3);
        res.emplace_back(cat, line, line, shortf);
    }
    return res;
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
    BookCreate(book);

    std::cout << "Вітаю в телефонному довіднику.\n";

    int choice;
    
    while (true) {
        std::cout << "Оберіть дію:\n";

        std::cout << "1. Вивести довідник.\n" 
                  << "2. Додати запис.\n"
                  << "3. Видалити запис. \n"
                  << "4. Пошук запису.\n"
                  << "0. Вийти.\n";    

        std::cin >> choice;
        std::cin.ignore();

        switch (choice){
            case(1):{
                int counter = 1;
                for(auto *record : book.getRecords()){
                    std::cout << "(" << counter++ << ")\n";
                    record->print();
                    std::cout << "--------------------------------------\n";
                }
                break;
            }
            case(2): { 
                std::cout << "1. Додати людину\n"
                          << "2. Додати компанію.\n"
                          << "0. Скасувати\n";
                int add;
                std::cin >> add;
                std::cin.ignore();

                switch(add) {
                    case 0: {
                        std::cout << "Скасовано.\n";
                        break;
                    }
                    case(1): {
                        std::string addname;
                        std::cout << "Введіть ПІБ:";
                        std::getline(std::cin, addname);

                        std::string addgender;
                        std::cout << "Введіть стать:";
                        std::getline(std::cin, addgender);

                        std::string addorg;
                        std::cout << "Введіть організацію (якщо є):";  
                        std::getline(std::cin, addorg);

                        std::vector<Phone> addphones = promptPhones();
                        std::vector<std::string> addemails = promptEmails();

                        Organization* orgptr = nullptr;
                        for (auto* record : book.getRecords()){
                            Organization* orgcheck = dynamic_cast<Organization*>(record);
                            if (orgcheck != nullptr && orgcheck->getTitle() == addorg){
                                orgptr = orgcheck;
                                break;
                            }
                        }
                        Person* newPerson = new Person(addname, addgender, orgptr, addphones, addemails);
                        book.addRecord(newPerson);
                        std::cout << "Запис додано.\n";
                        break;
                    }
                    case(2): {
                        std::string addtitle;
                        std::cout << "Введіть назву компанії:";
                        std::getline(std::cin, addtitle);

                        std::string addactivity;
                        std::cout << "Введіть діяльність компанії:";
                        std::getline(std::cin, addactivity);

                        std::vector<Phone> addphones = promptPhones();
                        std::vector<std::string> addemails = promptEmails();

                        std::string addmanager;
                        std::cout << "Введіть ПІБ керівника (якщо є):";
                        std::getline(std::cin, addmanager);

                        for (auto* record : book.getRecords()){
                            Person* personcheck = dynamic_cast<Person*>(record);
                            if (personcheck != nullptr && personcheck->getName() == addmanager){
                                personcheck->setOrganization(new Organization(addtitle, addactivity, nullptr, addphones, addemails));
                                break;
                            }
                        }
                        Organization* newOrg = new Organization(addtitle, addactivity, nullptr, addphones, addemails);
                        book.addRecord(newOrg);
                        std::cout << "Запис додано.\n";
                        break;
                    }
                }
                break;
            }
            case(3):{
                std::cout << "Оберіть номер запису (0 — скасувати):";
                int remove;
                std::cin >> remove;
                if (remove == 0) {
                    std::cout << "Скасовано.\n";
                } else {
                    book.removeRecord(remove + 1);
                    std::cout << "Запис видалено.\n";
                }
                break;
            }

            case(4):{
                std::cout << "Оберіть критерій пошуку:\n"
                          << "1. Пошук за іменем\n"
                          << "2. Пошук за номером телефону\n"
                          << "3. Пошук за email\n"
                          << "0. Скасувати\n";
                int search;
                std::cin >> search;
                std::cin.ignore();

                switch(search) {
                    case 0: {
                        std::cout << "Скасовано.\n";
                        break;
                    }
                    case 1: {
                        std::string name;
                        std::cout << "Введіть ім'я для пошуку:";
                        std::getline(std::cin, name);
                        auto foundByName = book.findByName(name);
                        if (foundByName.empty()) {
                            std::cout << "Записів не знайдено.\n";
                        } else {
                            for (auto* record : foundByName) {
                                record->print();
                                std::cout << "--------------------------------------\n";
                            }
                        }
                        break;
                    }
                    case 2: {
                        std::string phone;
                        std::cout << "Введіть номер телефону для пошуку:";
                        std::getline(std::cin, phone);
                        auto foundByPhone = book.findByPhone(phone);
                        if (foundByPhone.empty()) {
                            std::cout << "Записів не знайдено.\n";
                        } else {
                            for (auto* record : foundByPhone) {
                                record->print();
                                std::cout << "--------------------------------------\n";
                            }
                        }
                        break;
                    }
                    case 3: {
                        std::string email;
                        std::cout << "Введіть email для пошуку:";
                        std::getline(std::cin, email);
                        auto foundByEmail = book.findByEmail(email);
                        if (foundByEmail.empty()) {
                            std::cout << "Записів не знайдено.\n";
                        } else {
                            for (auto* record : foundByEmail) {
                                record->print();
                                std::cout << "--------------------------------------\n";
                            }
                        }
                        break;
                    }
                    default: {
                        std::cout << "Невірний вибір.\n";
                        break;
                    }
                }
                break;
            }

            case(0): {
                std::cout << "До побачення!\n";
                return 0;
            }
        }
    }              

}


