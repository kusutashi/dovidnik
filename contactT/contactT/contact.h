#include "contact.h"
#include <cstdio>

int main() {
    // Встановлюємо українську локалізацію для консолі (якщо підтримується)
    setlocale(LC_ALL, "Ukrainian");

    cout << "Ініціалізація телефонного довідника..." << endl;

    // Створюємо об'єкт телефонного довідника
    PhoneBook phoneBook("contacts.dat");

    int choice;

    cout << "\n?? Ласкаво просимо до Телефонного Довідника!" << endl;
    cout << "Програма готова до роботи." << endl;

    do {
        phoneBook.clearScreen();
        showMainMenu();
        cout << "Ваш вибір: ";
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
            cout << "\n?? Дякуємо за використання Телефонного Довідника!" << endl;
            cout << "Дані автоматично збережено." << endl;
            cout << "До побачення!" << endl;
            break;
        default:
            cout << "\n? Некоректний вибір!" << endl;
            cout << "Будь ласка, виберіть число від 0 до 9." << endl;
            phoneBook.pauseScreen();
            break;
        }

    } while (choice != 0);

    return 0;
}