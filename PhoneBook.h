#pragma once
#include <vector>
#include <string>
#include "Record.h"

class PhoneBook {
    private:
        std::vector<Record*> records;
    public:
        ~PhoneBook();

        void addRecord(Record* record);
        void removeRecord(int index);
        const std::vector<Record*>& getRecords() const { return records; }

        std::vector<Record*> findByName(const std::string& name) const;
        std::vector<Record*> findByPhone(const std::string& phoneNumber) const;
        std::vector<Record*> findByEmail(const std::string& searchEmail) const;
};

