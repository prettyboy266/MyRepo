#ifndef SPORTRECORD_H
#define SPORTRECORD_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Record {
public:
    std::string sport;
    std::string discipline;
    std::string type;
    std::string gender;
    std::string date;
    std::string name;
    std::string country;
    double achievement;
    friend std::ostream& operator<<(std::ostream& os, const Record& record);
    friend std::istream& operator>>(std::istream& is, Record& record);
    bool operator==(const Record& other) const;

   
};

class SportRecord {
private:
    std::vector<Record> records;
    const std::string filename = "records.txt";

public:
   
    void addRecord(const Record& record);
    void removeRecord(int index);

    void displayRecords();
    int calculateTotalRecords(const std::string& sport);
    void displayWorldRecordsForWomenLastYear();
    void menu();
    SportRecord& operator+=(const Record& record);
    friend std::ofstream& operator<<(std::ofstream& ofs, const SportRecord& sportRecord);
    friend std::ifstream& operator>>(std::ifstream& ifs, SportRecord& sportRecord);

    
};

#endif // SPORTRECORD_H
