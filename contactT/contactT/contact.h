#include "contact.h"
#include <cstdio>

int main() {
    // ������������ ��������� ���������� ��� ������ (���� �����������)
    setlocale(LC_ALL, "Ukrainian");

    cout << "����������� ����������� ��������..." << endl;

    // ��������� ��'��� ����������� ��������
    PhoneBook phoneBook("contacts.dat");

    int choice;

    cout << "\n?? ������� ������� �� ����������� ��������!" << endl;
    cout << "�������� ������ �� ������." << endl;

    do {
        phoneBook.clearScreen();
        showMainMenu();
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            phoneBook.addContact();
            break;
        case 2:
            phoneBook.editContact();
            break;
        case 3:
            phoneBook.deleteContact();
            break;
        case 4:
            phoneBook.displayAllContacts();
            break;
        case 5:
            phoneBook.searchContacts();
            break;
        case 6:
            phoneBook.sortContacts();
            break;
        case 7:
            phoneBook.manageBlacklist();
            break;
        case 8:
            phoneBook.generateBlacklistReport();
            break;
        case 9:
            phoneBook.checkBirthdays();
            break;
        case 0:
            cout << "\n?? ������ �� ������������ ����������� ��������!" << endl;
            cout << "��� ����������� ���������." << endl;
            cout << "�� ���������!" << endl;
            break;
        default:
            cout << "\n? ����������� ����!" << endl;
            cout << "���� �����, ������� ����� �� 0 �� 9." << endl;
            phoneBook.pauseScreen();
            break;
        }

    } while (choice != 0);

    return 0;
}