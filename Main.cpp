#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>

#include "Record.h"
#include "Person.h"
#include "Organization.h"
#include "PhoneBook.h"
#include "Person.cpp"     
#include "Organization.cpp" 
#include "PhoneBook.cpp"  

Phone generateRandomPhone() {
    std::vector<std::string> phoneCodes = {"050", "067", "093", "063"};
    std::string code = phoneCodes[rand() % phoneCodes.size()];

    std::string number = "";
    for(int i = 0; i < 7; ++i) {
        number += std::to_string(rand() % 10);
    }

    std::string cat;
    switch (rand() % 3) {
        case 0: cat = "Домашній"; break;
        case 1: cat = "Мобільний"; break;
        case 2: cat = "Робочий"; break;
    }

    std::string full = "+38" + code + number;
    std::string medium = code + number.substr(0, 7);
    std::string shortt = number.substr(0,3) + "-" + number.substr(3);

    return Phone(cat, full, medium, shortt);
}

void BookCreate(PhoneBook& book) {
    std::vector<std::string> maleNames = {"Шевченко Тарас Григорович", "Сукачук Андрій Миколайович", "Ковальський Руслан Станіславович", "Політаєв Артур Дмитрович", "Маркарян Арсен Ашотович"};
    std::vector<std::string> femaleNames = {"Самоварова Ірина Ігнатівна", "Кочерга Марія Степанівна", "Гнатюк Роксолана Іванівна", "Тейт Наталія Андріївна", "Українка Кристина Петрусівна"};
    std::vector<std::string> organizations = {"Київстар", "BasedBodyworks", "Пузата Хата", "Asics", "Anuken"};
    std::vector<std::string> activities = {"Взуття", "Продажі", "Готель", "Оренда", "Атомна енергетика"};
    std::vector<std::string> emails = {"contact@gmail.com", "info@baza.ua", "office@kahoot.com", "admin@receipt.com", "support@thisandthat.com"};

    std::vector<Person*> persons;
    std::vector<Organization*> orgs;

    for (int i = 0; i < 10; ++i) {
        int phonesCount = rand() % 4 + 1;
        int emailsCount = rand() % 4 + 1; 

        std::vector<Phone> phones;
        for (int p = 0; p < phonesCount; ++p) phones.push_back(generateRandomPhone());

        std::vector<std::string> ems;
        for (int e = 0; e < emailsCount; ++e) ems.push_back(emails[rand() % emails.size()]);

        if (rand() % 2 == 0) { // org
            std::string title = organizations[rand() % organizations.size()];
            std::string activity = activities[rand() % activities.size()];
            Organization* org = new Organization(title, activity, nullptr, phones, ems);
            orgs.push_back(org);
            book.addRecord(org);
        } else { // person
            int genderRand = rand() % 2;
            std::string name;
            std::string gender;
            if (genderRand == 0) {
                name = maleNames[rand() % maleNames.size()];
                gender = "чоловіча";
            } else {
                name = femaleNames[rand() % femaleNames.size()];
                gender = "жіноча";
            }
            Person* pptr = new Person(name, gender, nullptr, phones, ems);
            persons.push_back(pptr);
            book.addRecord(pptr);
        }
    }

    for (Person* p : persons) {
        if (!orgs.empty() && (rand() % 2 == 0)) {
            Organization* org = orgs[rand() % orgs.size()];
            p->setOrganization(org);
        }
    }

    for (Organization* org : orgs) {
        if (!persons.empty() && (rand() % 2 == 0)) {
            Person* m = persons[rand() % persons.size()];
            org->setManager(m);
            m->setOrganization(org);
        }
    }
}

std::string choosePhoneCategory() {
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
            case 1: return "Домашній";
            case 2: return "Мобільний";
            case 3: return "Робочий";
            default: std::cout << "Невірний вибір, спробуйте ще.\n";
        }
    }
}

std::vector<Phone> enterPhones() {
    std::vector<Phone> res;
    while (true) {
        std::cout << "Введіть номер телефону (або пустий рядок щоб завершити, формат +380XXYYYYYYY): ";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) break;
        if(line.substr(0, 3) != "+38" && line.size() != 13) {
            std::cout << "Невірний формат номера. Спробуйте ще раз.\n";
            continue;
        }
        std::string cat = choosePhoneCategory();
        std::string digits = line.substr(1);
        std::string medium = digits.substr(0, 9);
        std::string shortf = digits.substr(digits.size() - 7);
        res.push_back(Phone(cat, line, medium, shortf));
    }
    return res;
}

std::vector<std::string> enterEmails() {
    std::vector<std::string> res;
    while (true) {
        std::cout << "Введіть email (або пустий рядок щоб завершити): ";
        std::string e;
        std::getline(std::cin, e);
        if (e.empty()) break;
        res.push_back(e);
    }
    return res;
}

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

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
                  << "0. Вийти.\n"
                  << ">>> ";

        std::cin >> choice;
        std::cin.ignore();

        switch (choice){
            case 1: {
                int counter = 1;
                for(auto *record : book.getRecords()){
                    std::cout << "(" << counter++ << ")\n";
                    record->print();
                    std::cout << "--------------------------------------\n";
                }
                break;
            }
            case 2: {
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
                    case 1: {
                        std::string addname;
                        std::cout << "Введіть ПІБ: ";
                        std::getline(std::cin, addname);

                        std::string addgender;
                        std::cout << "Введіть стать: ";
                        std::getline(std::cin, addgender);

                        Organization* orgptr = nullptr;
                        while (true) {
                            std::string addorg;
                            std::cout << "Введіть організацію (якщо є): ";
                            std::getline(std::cin, addorg);
                            if (addorg.empty()) break;

                            for (auto* record : book.getRecords()){
                                Organization* orgcheck = dynamic_cast<Organization*>(record);
                                if (orgcheck != nullptr && orgcheck->getTitle() == addorg){
                                    orgptr = orgcheck;
                                    break;
                                }
                            }

                            if (orgptr != nullptr) break;
                            std::cout << "Організація '" << addorg << "' не знайдена. Спробуйте ще раз.\n";
                        }

                        std::vector<Phone> addphones = enterPhones();
                        std::vector<std::string> addemails = enterEmails();

                        Person* newPerson = new Person(addname, addgender, orgptr, addphones, addemails);
                        book.addRecord(newPerson);
                        std::cout << "Запис додано.\n";
                        break;
                    }
                    case 2: {
                        std::string addtitle;
                        std::cout << "Введіть назву компанії: ";
                        std::getline(std::cin, addtitle);

                        std::string addactivity;
                        std::cout << "Введіть діяльність компанії: ";
                        std::getline(std::cin, addactivity);

                        std::vector<Phone> addphones = enterPhones();
                        std::vector<std::string> addemails = enterEmails();

                        Person* managerPtr = nullptr;
                        while (true) {
                            std::string addmanager;
                            std::cout << "Введіть ПІБ керівника (якщо є): ";
                            std::getline(std::cin, addmanager);
                            if (addmanager.empty()) break;

                            for (auto* record : book.getRecords()){
                                Person* personcheck = dynamic_cast<Person*>(record);
                                if (personcheck != nullptr && personcheck->getName() == addmanager){
                                    managerPtr = personcheck;
                                    break;
                                }
                            }

                            if (managerPtr != nullptr) break;
                            std::cout << "Керівника '" << addmanager << "' не знайдено. Спробуйте ще раз.\n";
                        }

                        Organization* newOrg = new Organization(addtitle, addactivity, nullptr, addphones, addemails);
                        if (managerPtr != nullptr) {
                            newOrg->setManager(managerPtr);
                            managerPtr->setOrganization(newOrg);
                        }
                        book.addRecord(newOrg);
                        std::cout << "Запис додано.\n";
                        break;
                    }
                }
                break;
            }
            case 3: {
                std::cout << "Оберіть номер запису (0 — скасувати):";
                int remove;
                std::cin >> remove;
                if (remove == 0) {
                    std::cout << "Скасовано.\n";
                } else {
                    book.removeRecord(remove - 1);
                    std::cout << "Запис видалено.\n";
                }
                break;
            }
            case 4: {
                std::cout << "Оберіть критерій пошуку:\n"
                          << "1. Пошук за іменем\n"
                          << "2. Пошук за номером телефону\n"
                          << "3. Пошук за email\n"
                          << "0. Скасувати\n";
                int search;
                std::cin >> search;
                std::cin.ignore();

                switch (search) {
                    case 0: std::cout << "Скасовано.\n"; break;
                    case 1: {
                        std::string name;
                        std::cout << "Введіть ім'я для пошуку:";
                        std::getline(std::cin, name);
                        auto foundByName = book.findByName(name);
                        if (foundByName.empty()) {
                            std::cout << "Записів не знайдено.\n";
                        } else {
                            for (auto* record : foundByName){
                                record->print();
                                std::cout << "--------------------------------------\n";
                            }
                        }
                        break;
                    }
                    case 2: {
                        std::string phone;
                        std::cout << "Введіть номер телефону для пошуку: ";
                        std::getline(std::cin, phone);
                        auto foundByPhone = book.findByPhone(phone);
                        if (foundByPhone.empty()) {
                            std::cout << "Записів не знайдено.\n";
                        } else {
                            for (auto* record : foundByPhone){
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
                            for (auto* record : foundByEmail){
                                record->print();
                                std::cout << "--------------------------------------\n";
                            }
                        }
                        break;
                    }
                    default: std::cout << "Невірний вибір.\n"; break;
                }
                break;
            }
            case 0: {
                std::cout << "До побачення!\n";
                return 0;
            }
            default: std::cout << "Невірний вибір.\n"; break;
        }
    }
}
