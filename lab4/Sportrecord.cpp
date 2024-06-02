#include "SportRecord.h"
#include <iostream>
#include <fstream>
//

void SportRecord::addRecord(const Record& record) {
    records.push_back(record);
}

void SportRecord::removeRecord(int index) {
    if (index >= 0 && index < records.size()) {
        records.erase(records.begin() + index);
    }
}

std::ostream& operator<<(std::ostream& os, const Record& record) {
    os << record.sport << " " << record.discipline << " " << record.type << " "
        << record.gender << " " << record.date << " " << record.name << " "
        << record.country << " " << record.achievement;
    return os;
}

std::istream& operator>>(std::istream& is, Record& record) {
    is >> record.sport >> record.discipline >> record.type >> record.gender
        >> record.date >> record.name >> record.country >> record.achievement;
    return is;
}

bool Record::operator==(const Record& other) const {
    return sport == other.sport && discipline == other.discipline && type == other.type &&
        gender == other.gender && date == other.date && name == other.name &&
        country == other.country && achievement == other.achievement;
}

SportRecord& SportRecord::operator+=(const Record& record) {
    addRecord(record);
    return *this;
}

std::ofstream& operator<<(std::ofstream& ofs, const SportRecord& sportRecord) {
    if (!ofs) {
        std::cerr << "Failed to open file stream for writing." << std::endl;
        return ofs;
    }
    for (const auto& record : sportRecord.records) {
        ofs << record << std::endl;
    }
    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, SportRecord& sportRecord) {
    if (!ifs) {
        std::cerr << "Failed to open file stream for reading." << std::endl;
        return ifs;
    }
    sportRecord.records.clear();
    Record record;
    while (ifs >> record) {
        sportRecord.records.push_back(record);
    }
    return ifs;
}

void SportRecord::displayRecords() {
    for (const auto& record : records) {
        std::cout << record << std::endl;
    }
}

int SportRecord::calculateTotalRecords(const std::string& sport) {
    int totalRecords = 0;
    for (const auto& record : records) {
        if (record.sport == sport) {
            totalRecords++;
        }
    }
    return totalRecords;
}

void SportRecord::displayWorldRecordsForWomenLastYear() {
    std::cout << "World records set by women in the last year:" << std::endl;
    // TODO: Implement the logic to check if the record was set within the last year
    for (const auto& record : records) {
        if (record.type == "world" && record.gender == "female" && std::stoi(record.date) >= 2022) {
            std::cout << record << std::endl;
        }
    }
}

void SportRecord::menu() {
    int choice;
    do {
        std::cout << "1. Add a record\n";
        std::cout << "2. Remove a record (Enter index)\n";
        std::cout << "3. Display records\n";
        std::cout << "4. Calculate total records for a given sport\n";
        std::cout << "5. Display world records set by women in the last year\n";
        std::cout << "6. Save to file\n";
        std::cout << "7. Load from file\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            Record record;
            std::cout << "Enter the details for the new record:\n";
            if (std::cin >> record) {  // Read the record using overloaded operator>>
                *this += record; // Add the record using overloaded operator+=
            }
            else {
                std::cin.clear(); // clear the error from cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
            }
            break;
        }
        case 2: {
            int index;
            std::cout << "Enter the index of the record to remove: ";
            std::cin >> index;
            removeRecord(index);
            break;
        }
        case 3: {
            for (const auto& record : records) {
                std::cout << record << std::endl; // Use the overloaded operator<<
            }
            break;
        }
        case 4: {
            std::string sport;
            std::cout << "Enter the sport: ";
            std::cin >> sport;
            int totalRecords = calculateTotalRecords(sport);
            std::cout << "Total records for " << sport << ": " << totalRecords << std::endl;
            break;
        }
        case 5: {
            displayWorldRecordsForWomenLastYear();
            break;
        }
        case 6: {
            std::ofstream ofs(filename);
            if (ofs) {
                ofs << *this;  // Save to file using overloaded operator<<
            }
            ofs.close();
            break;
        }
        case 7: {
            std::ifstream ifs(filename);
            if (ifs) {
                ifs >> *this;  // Load from file using overloaded operator>>
            }
            ifs.close();
            break;
        }
        case 8: {
            std::cout << "Exiting program.\n";
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}
