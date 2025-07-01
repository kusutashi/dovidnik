#pragma once
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_CONTACTS = 1000;
const int MAX_STRING_LENGTH = 100;


int myStrlen(const char* str);
void myStrcpy(char* dest, const char* src);
int myStrcmp(const char* str1, const char* str2);
char* myStrstr(const char* haystack, const char* needle);
void myItoa(int num, char* str);
int myAtoi(const char* str);

struct Date {
    int day;
    int month;
    int year;

    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    void toString(char* buffer) const {
        char dayStr[10], monthStr[10], yearStr[10];
        myItoa(day, dayStr);
        myItoa(month, monthStr);
        myItoa(year, yearStr);

        buffer[0] = '\0';
        if (day < 10) {
            buffer[0] = '0';
            buffer[1] = '\0';
        }
        myStrcpy(buffer + myStrlen(buffer), dayStr);
        myStrcpy(buffer + myStrlen(buffer), "/");

        if (month < 10) {
            myStrcpy(buffer + myStrlen(buffer), "0");
        }
        myStrcpy(buffer + myStrlen(buffer), monthStr);
        myStrcpy(buffer + myStrlen(buffer), "/");
        myStrcpy(buffer + myStrlen(buffer), yearStr);
    }

    bool isValid() const {
        return day > 0 && day <= 31 && month > 0 && month <= 12 && year > 1900;
    }
};

struct Contact {
    char surname[MAX_STRING_LENGTH];
    char name[MAX_STRING_LENGTH];
    char homePhone[MAX_STRING_LENGTH];
    char workPhone[MAX_STRING_LENGTH];
    char homeAddress[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
    Date birthDate;
    char group[MAX_STRING_LENGTH];
    bool isBlacklisted;

    Contact() : isBlacklisted(false) {
        surname[0] = '\0';
        name[0] = '\0';
        homePhone[0] = '\0';
        workPhone[0] = '\0';
        homeAddress[0] = '\0';
        email[0] = '\0';
        group[0] = '\0';
    }

    void display() const {
        char dateStr[20];
        birthDate.toString(dateStr);

        cout << "\n=== КОНТАКТ ===" << endl;
        cout << "Прізвище: " << surname << endl;
        cout << "Ім'я: " << name << endl;
        cout << "Дом. телефон: " << homePhone << endl;
        cout << "Роб. телефон: " << workPhone << endl;
        cout << "Дом. адреса: " << homeAddress << endl;
        cout << "Ел. адреса: " << email << endl;
        cout << "Дата народження: " << dateStr << endl;
        cout << "Група: " << group << endl;
        cout << "Чорний список: " << (isBlacklisted ? "Так" : "Ні") << endl;
        cout << "===============" << endl;
    }
};

class PhoneBook {
private:
    Contact contacts[MAX_CONTACTS];
    int contactCount;
    char filename[MAX_STRING_LENGTH];

public:
    PhoneBook(const char* file = "contacts.dat") : contactCount(0) {
        myStrcpy(filename, file);
        loadFromFile();
    }

    ~PhoneBook() {
        saveToFile();
    }


    void addContact();
    void editContact();
    void deleteContact();
    void displayAllContacts() const;
    void searchContacts();
    void sortContacts();
    void manageBlacklist();
    void generateBlacklistReport() const;
    void checkBirthdays() const;


    void saveToFile() const;
    void loadFromFile();


    void clearScreen() const;
    void pauseScreen() const;
    Date inputDate() const;
    void toLowerCase(char* str) const;
    bool isDateWithinDays(const Date& date, int days) const;
    int findContactIndex() const;
    bool containsIgnoreCase(const char* str, const char* substr) const;
    void getInputLine(char* buffer, int maxLength);


    void sortBySurname();
    void sortByName();
    void sortByGroup();
    void sortByBirthDate();


    void copyContact(Contact& dest, const Contact& src);
    void swapContacts(int index1, int index2);
};


void showMainMenu();
void showSearchMenu();
void showSortMenu();

#endif