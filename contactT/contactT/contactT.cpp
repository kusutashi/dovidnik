#include "contact.h"
#include <cstdio>

int myStrlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void myStrcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int myStrcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) return -1;
        if (str1[i] > str2[i]) return 1;
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') return 0;
    if (str1[i] == '\0') return -1;
    return 1;
}

char* myStrstr(const char* haystack, const char* needle) {
    if (*needle == '\0') return (char*)haystack;

    for (int i = 0; haystack[i] != '\0'; i++) {
        bool found = true;
        for (int j = 0; needle[j] != '\0'; j++) {
            if (haystack[i + j] != needle[j]) {
                found = false;
                break;
            }
        }
        if (found) return (char*)(haystack + i);
    }
    return NULL;
}

void myItoa(int num, char* str) {
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    bool negative = false;
    if (num < 0) {
        negative = true;
        num = -num;
    }

    char temp[50];
    int i = 0;

    while (num > 0) {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    }

    int idx = 0;
    if (negative) {
        str[idx++] = '-';
    }

    for (int j = i - 1; j >= 0; j--) {
        str[idx++] = temp[j];
    }
    str[idx] = '\0';
}

int myAtoi(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

void PhoneBook::clearScreen() const {
    // Простий спосіб очищення екрану
    for (int i = 0; i < 50; i++) {
        cout << endl;
    }
}

void PhoneBook::pauseScreen() const {
    cout << "\nНатисніть Enter для продовження...";
    cin.ignore();
    cin.get();
}

void PhoneBook::toLowerCase(char* str) const {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

bool PhoneBook::containsIgnoreCase(const char* str, const char* substr) const {
    char lowerStr[MAX_STRING_LENGTH];
    char lowerSubstr[MAX_STRING_LENGTH];

    myStrcpy(lowerStr, str);
    myStrcpy(lowerSubstr, substr);

    toLowerCase(lowerStr);
    toLowerCase(lowerSubstr);

    return myStrstr(lowerStr, lowerSubstr) != NULL;
}

void PhoneBook::getInputLine(char* buffer, int maxLength) {
    cin.getline(buffer, maxLength);

    int len = myStrlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

Date PhoneBook::inputDate() const {
    Date date;
    cout << "Введіть день (1-31): ";
    cin >> date.day;
    cout << "Введіть місяць (1-12): ";
    cin >> date.month;
    cout << "Введіть рік (наприклад, 1990): ";
    cin >> date.year;

    if (!date.isValid()) {
        cout << "Некоректна дата! Встановлено 01/01/1900" << endl;
        return Date(1, 1, 1900);
    }

    return date;
}

void PhoneBook::copyContact(Contact& dest, const Contact& src) {
    myStrcpy(dest.surname, src.surname);
    myStrcpy(dest.name, src.name);
    myStrcpy(dest.homePhone, src.homePhone);
    myStrcpy(dest.workPhone, src.workPhone);
    myStrcpy(dest.homeAddress, src.homeAddress);
    myStrcpy(dest.email, src.email);
    dest.birthDate = src.birthDate;
    myStrcpy(dest.group, src.group);
    dest.isBlacklisted = src.isBlacklisted;
}

void PhoneBook::swapContacts(int index1, int index2) {
    Contact temp;
    copyContact(temp, contacts[index1]);
    copyContact(contacts[index1], contacts[index2]);
    copyContact(contacts[index2], temp);
}

void PhoneBook::addContact() {
    clearScreen();
    cout << "=== ДОДАВАННЯ КОНТАКТУ ===" << endl;

    if (contactCount >= MAX_CONTACTS) {
        cout << "Досягнуто максимальну кількість контактів!" << endl;
        pauseScreen();
        return;
    }

    Contact& contact = contacts[contactCount];
    cin.ignore();

    cout << "Прізвище: ";
    getInputLine(contact.surname, MAX_STRING_LENGTH);

    cout << "Ім'я: ";
    getInputLine(contact.name, MAX_STRING_LENGTH);

    cout << "Дом. телефон: ";
    getInputLine(contact.homePhone, MAX_STRING_LENGTH);

    cout << "Роб. телефон: ";
    getInputLine(contact.workPhone, MAX_STRING_LENGTH);

    cout << "Дом. адреса: ";
    getInputLine(contact.homeAddress, MAX_STRING_LENGTH);

    cout << "Ел. адреса: ";
    getInputLine(contact.email, MAX_STRING_LENGTH);

    cout << "Дата народження:" << endl;
    contact.birthDate = inputDate();

    cin.ignore();
    cout << "Група (сім'я/колеги/друзі/інше): ";
    getInputLine(contact.group, MAX_STRING_LENGTH);

    char choice;
    cout << "Додати до чорного списку? (y/n): ";
    cin >> choice;
    contact.isBlacklisted = (choice == 'y' || choice == 'Y');

    contactCount++;
    cout << "\nКонтакт успішно додано!" << endl;
    pauseScreen();
}

int PhoneBook::findContactIndex() const {
    if (contactCount == 0) {
        cout << "Список контактів порожній!" << endl;
        return -1;
    }

    cout << "\n=== СПИСОК КОНТАКТІВ ===" << endl;
    for (int i = 0; i < contactCount; ++i) {
        cout << i + 1 << ". " << contacts[i].surname << " "
            << contacts[i].name << endl;
    }

    int index;
    cout << "\nВведіть номер контакту: ";
    cin >> index;

    if (index < 1 || index > contactCount) {
        cout << "Некоректний номер контакту!" << endl;
        return -1;
    }

    return index - 1;
}

void PhoneBook::editContact() {
    clearScreen();
    cout << "=== РЕДАГУВАННЯ КОНТАКТУ ===" << endl;

    int index = findContactIndex();
    if (index == -1) {
        pauseScreen();
        return;
    }

    Contact& contact = contacts[index];
    contact.display();

    cout << "\nЩо бажаєте редагувати?" << endl;
    cout << "1. Прізвище" << endl;
    cout << "2. Ім'я" << endl;
    cout << "3. Дом. телефон" << endl;
    cout << "4. Роб. телефон" << endl;
    cout << "5. Дом. адреса" << endl;
    cout << "6. Ел. адреса" << endl;
    cout << "7. Дата народження" << endl;
    cout << "8. Група" << endl;
    cout << "9. Чорний список" << endl;
    cout << "0. Повернутися" << endl;

    int choice;
    cout << "Ваш вибір: ";
    cin >> choice;

    cin.ignore();

    switch (choice) {
    case 1:
        cout << "Нове прізвище: ";
        getInputLine(contact.surname, MAX_STRING_LENGTH);
        break;
    case 2:
        cout << "Нове ім'я: ";
        getInputLine(contact.name, MAX_STRING_LENGTH);
        break;
    case 3:
        cout << "Новий дом. телефон: ";
        getInputLine(contact.homePhone, MAX_STRING_LENGTH);
        break;
    case 4:
        cout << "Новий роб. телефон: ";
        getInputLine(contact.workPhone, MAX_STRING_LENGTH);
        break;
    case 5:
        cout << "Нова дом. адреса: ";
        getInputLine(contact.homeAddress, MAX_STRING_LENGTH);
        break;
    case 6:
        cout << "Нова ел. адреса: ";
        getInputLine(contact.email, MAX_STRING_LENGTH);
        break;
    case 7:
        cout << "Нова дата народження:" << endl;
        contact.birthDate = inputDate();
        break;
    case 8:
        cout << "Нова група: ";
        getInputLine(contact.group, MAX_STRING_LENGTH);
        break;
    case 9: {
        char bl;
        cout << "Чорний список (y/n): ";
        cin >> bl;
        contact.isBlacklisted = (bl == 'y' || bl == 'Y');
        break;
    }
    case 0:
        return;
    default:
        cout << "Некоректний вибір!" << endl;
        pauseScreen();
        return;
    }

    cout << "\nКонтакт успішно оновлено!" << endl;
    pauseScreen();
}

void PhoneBook::deleteContact() {
    clearScreen();
    cout << "=== ВИДАЛЕННЯ КОНТАКТУ ===" << endl;

    int index = findContactIndex();
    if (index == -1) {
        pauseScreen();
        return;
    }

    contacts[index].display();

    char confirm;
    cout << "\nВи впевнені, що хочете видалити цей контакт? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {

        for (int i = index; i < contactCount - 1; i++) {
            copyContact(contacts[i], contacts[i + 1]);
        }
        contactCount--;
        cout << "Контакт успішно видалено!" << endl;
    }
    else {
        cout << "Видалення скасовано." << endl;
    }

    pauseScreen();
}

void PhoneBook::displayAllContacts() const {
    clearScreen();
    cout << "=== ВСІ КОНТАКТИ ===" << endl;

    if (contactCount == 0) {
        cout << "Список контактів порожній!" << endl;
        pauseScreen();
        return;
    }

    for (int i = 0; i < contactCount; i++) {
        contacts[i].display();
        cout << endl;
    }

    pauseScreen();
}

void PhoneBook::searchContacts() {
    clearScreen();
    showSearchMenu();

    int choice;
    cout << "Ваш вибір: ";
    cin >> choice;

    char searchTerm[MAX_STRING_LENGTH];
    Contact results[MAX_CONTACTS];
    int resultCount = 0;

    cin.ignore();

    switch (choice) {
    case 1:
        cout << "Введіть прізвище: ";
        getInputLine(searchTerm, MAX_STRING_LENGTH);
        for (int i = 0; i < contactCount; i++) {
            if (containsIgnoreCase(contacts[i].surname, searchTerm)) {
                copyContact(results[resultCount], contacts[i]);
                resultCount++;
            }
        }
        break;
    case 2:
        cout << "Введіть ім'я: ";
        getInputLine(searchTerm, MAX_STRING_LENGTH);
        for (int i = 0; i < contactCount; i++) {
            if (containsIgnoreCase(contacts[i].name, searchTerm)) {
                copyContact(results[resultCount], contacts[i]);
                resultCount++;
            }
        }
        break;
    case 3:
        cout << "Введіть телефон: ";
        getInputLine(searchTerm, MAX_STRING_LENGTH);
        for (int i = 0; i < contactCount; i++) {
            if (myStrstr(contacts[i].homePhone, searchTerm) != NULL ||
                myStrstr(contacts[i].workPhone, searchTerm) != NULL) {
                copyContact(results[resultCount], contacts[i]);
                resultCount++;
            }
        }
        break;
    case 4:
        cout << "Введіть групу: ";
        getInputLine(searchTerm, MAX_STRING_LENGTH);
        for (int i = 0; i < contactCount; i++) {
            if (containsIgnoreCase(contacts[i].group, searchTerm)) {
                copyContact(results[resultCount], contacts[i]);
                resultCount++;
            }
        }
        break;
    case 5:
        cout << "Введіть email: ";
        getInputLine(searchTerm, MAX_STRING_LENGTH);
        for (int i = 0; i < contactCount; i++) {
            if (containsIgnoreCase(contacts[i].email, searchTerm)) {
                copyContact(results[resultCount], contacts[i]);
                resultCount++;
            }
        }
        break;
    case 0:
        return;
    default:
        cout << "Некоректний вибір!" << endl;
        pauseScreen();
        return;
    }

    clearScreen();
    cout << "=== РЕЗУЛЬТАТИ ПОШУКУ ===" << endl;

    if (resultCount == 0) {
        cout << "Нічого не знайдено!" << endl;
    }
    else {
        for (int i = 0; i < resultCount; i++) {
            results[i].display();
            cout << endl;
        }
    }

    pauseScreen();
}

void PhoneBook::sortBySurname() {
    for (int i = 0; i < contactCount - 1; i++) {
        for (int j = 0; j < contactCount - i - 1; j++) {
            if (myStrcmp(contacts[j].surname, contacts[j + 1].surname) > 0) {
                swapContacts(j, j + 1);
            }
        }
    }
}

void PhoneBook::sortByName() {
    for (int i = 0; i < contactCount - 1; i++) {
        for (int j = 0; j < contactCount - i - 1; j++) {
            if (myStrcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                swapContacts(j, j + 1);
            }
        }
    }
}

void PhoneBook::sortByGroup() {
    for (int i = 0; i < contactCount - 1; i++) {
        for (int j = 0; j < contactCount - i - 1; j++) {
            if (myStrcmp(contacts[j].group, contacts[j + 1].group) > 0) {
                swapContacts(j, j + 1);
            }
        }
    }
}

void PhoneBook::sortByBirthDate() {
    for (int i = 0; i < contactCount - 1; i++) {
        for (int j = 0; j < contactCount - i - 1; j++) {
            bool shouldSwap = false;

            if (contacts[j].birthDate.year > contacts[j + 1].birthDate.year) {
                shouldSwap = true;
            }
            else if (contacts[j].birthDate.year == contacts[j + 1].birthDate.year) {
                if (contacts[j].birthDate.month > contacts[j + 1].birthDate.month) {
                    shouldSwap = true;
                }
                else if (contacts[j].birthDate.month == contacts[j + 1].birthDate.month) {
                    if (contacts[j].birthDate.day > contacts[j + 1].birthDate.day) {
                        shouldSwap = true;
                    }
                }
            }

            if (shouldSwap) {
                swapContacts(j, j + 1);
            }
        }
    }
}

void PhoneBook::sortContacts() {
    clearScreen();
    showSortMenu();

    int choice;
    cout << "Ваш вибір: ";
    cin >> choice;

    switch (choice) {
    case 1:
        sortBySurname();
        cout << "Контакти відсортовано за прізвищем!" << endl;
        break;
    case 2:
        sortByName();
        cout << "Контакти відсортовано за ім'ям!" << endl;
        break;
    case 3:
        sortByGroup();
        cout << "Контакти відсортовано за групою!" << endl;
        break;
    case 4:
        sortByBirthDate();
        cout << "Контакти відсортовано за датою народження!" << endl;
        break;
    case 0:
        return;
    default:
        cout << "Некоректний вибір!" << endl;
        pauseScreen();
        return;
    }

    pauseScreen();
}

void PhoneBook::manageBlacklist() {
    clearScreen();
    cout << "=== УПРАВЛІННЯ ЧОРНИМ СПИСКОМ ===" << endl;
    cout << "1. Показати чорний список" << endl;
    cout << "2. Додати до чорного списку" << endl;
    cout << "3. Видалити з чорного списку" << endl;
    cout << "0. Повернутися" << endl;

    int choice;
    cout << "Ваш вибір: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        clearScreen();
        cout << "=== ЧОРНИЙ СПИСОК ===" << endl;
        bool found = false;
        for (int i = 0; i < contactCount; i++) {
            if (contacts[i].isBlacklisted) {
                contacts[i].display();
                found = true;
            }
        }
        if (!found) {
            cout << "Чорний список порожній!" << endl;
        }
        pauseScreen();
        break;
    }
    case 2: {
        int index = findContactIndex();
        if (index != -1) {
            contacts[index].isBlacklisted = true;
            cout << "Контакт додано до чорного списку!" << endl;
        }
        pauseScreen();
        break;
    }
    case 3: {
        int index = findContactIndex();
        if (index != -1) {
            contacts[index].isBlacklisted = false;
            cout << "Контакт видалено з чорного списку!" << endl;
        }
        pauseScreen();
        break;
    }
    case 0:
        return;
    default:
        cout << "Некоректний вибір!" << endl;
        pauseScreen();
    }
}

void PhoneBook::generateBlacklistReport() const {
    clearScreen();
    cout << "=== ЗВІТ ЧОРНОГО СПИСКУ ===" << endl;
    cout << "ЗВІТ КОНТАКТІВ ІЗ ЧОРНОГО СПИСКУ" << endl;
    cout << "================================" << endl << endl;

    bool found = false;
    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].isBlacklisted) {
            cout << "Прізвище: " << contacts[i].surname << endl;
            cout << "Ім'я: " << contacts[i].name << endl;
            cout << "Дом. телефон: " << contacts[i].homePhone << endl;
            cout << "Роб. телефон: " << contacts[i].workPhone << endl;
            cout << "Дом. адреса: " << contacts[i].homeAddress << endl;
            cout << "Ел. адреса: " << contacts[i].email << endl;
            cout << "Група: " << contacts[i].group << endl;
            cout << "--------------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Чорний список порожній!" << endl;
    }

    cout << "\nЗвіт виведено на екран" << endl;
    pauseScreen();
}

bool PhoneBook::isDateWithinDays(const Date& date, int days) const {

    Date currentDate(1, 7, 2025); 


    Date thisYearBirthday(date.day, date.month, currentDate.year);

    int currentDayOfYear = currentDate.month * 30 + currentDate.day;
    int birthdayDayOfYear = thisYearBirthday.month * 30 + thisYearBirthday.day;


    int diff = birthdayDayOfYear - currentDayOfYear;
    return (diff >= 0 && diff <= days) || (diff < 0 && diff + 365 <= days);
}

void PhoneBook::checkBirthdays() const {
    clearScreen();
    cout << "=== НАГАДУВАННЯ ПРО ДНІ НАРОДЖЕННЯ ===" << endl;

    cout << "Дні народження в найближчі 3 дні:" << endl;
    cout << "===================================" << endl;

    bool found = false;

    for (int i = 0; i < contactCount; i++) {
        if (isDateWithinDays(contacts[i].birthDate, 3)) {
            cout << "\n🎂 УВАГА! Незабаром день народження!" << endl;
            cout << "Ім'я: " << contacts[i].name << " " << contacts[i].surname << endl;

            char dateStr[20];
            contacts[i].birthDate.toString(dateStr);
            cout << "Дата народження: " << dateStr << endl;

            cout << "Група: " << contacts[i].group << endl;

            if (myStrlen(contacts[i].homePhone) > 0) {
                cout << "Дом. телефон: " << contacts[i].homePhone << endl;
            }
            if (myStrlen(contacts[i].workPhone) > 0) {
                cout << "Роб. телефон: " << contacts[i].workPhone << endl;
            }

            cout << "--------------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Найближчих днів народження не знайдено." << endl;
        cout << "(Перевіряються дні народження на найближчі 3 дні)" << endl;
    }

    pauseScreen();
}





void showMainMenu() {
    cout << "\n======== ТЕЛЕФОННИЙ ДОВІДНИК ========" << endl;
    cout << "1. Додати контакт" << endl;
    cout << "2. Редагувати контакт" << endl;
    cout << "3. Видалити контакт" << endl;
    cout << "4. Показати всі контакти" << endl;
    cout << "5. Пошук контактів" << endl;
    cout << "6. Сортування контактів" << endl;
    cout << "7. Управління чорним списком" << endl;
    cout << "8. Генерувати звіт чорного списку" << endl;
    cout << "9. Нагадування про дні народження" << endl;
    cout << "0. Вихід" << endl;
    cout << "====================================" << endl;
}

void showSearchMenu() {
    cout << "\n=== ПОШУК КОНТАКТІВ ===" << endl;
    cout << "1. Пошук за прізвищем" << endl;
    cout << "2. Пошук за ім'ям" << endl;
    cout << "3. Пошук за телефоном" << endl;
    cout << "4. Пошук за групою" << endl;
    cout << "5. Пошук за email" << endl;
    cout << "0. Повернутися" << endl;
}

void showSortMenu() {
    cout << "\n=== СОРТУВАННЯ КОНТАКТІВ ===" << endl;
    cout << "1. Сортувати за прізвищем" << endl;
    cout << "2. Сортувати за ім'ям" << endl;
    cout << "3. Сортувати за групою" << endl;
    cout << "4. Сортувати за датою народження" << endl;
    cout << "0. Повернутися" << endl;
}


void PhoneBook::saveToFile() const {

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }


    fprintf(file, "%d\n", contactCount);


    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "%s\n", contacts[i].surname);
        fprintf(file, "%s\n", contacts[i].name);
        fprintf(file, "%s\n", contacts[i].homePhone);
        fprintf(file, "%s\n", contacts[i].workPhone);
        fprintf(file, "%s\n", contacts[i].homeAddress);
        fprintf(file, "%s\n", contacts[i].email);
        fprintf(file, "%d %d %d\n", contacts[i].birthDate.day,
            contacts[i].birthDate.month, contacts[i].birthDate.year);
        fprintf(file, "%s\n", contacts[i].group);
        fprintf(file, "%d\n", contacts[i].isBlacklisted ? 1 : 0);
    }

    fclose(file);
}

void PhoneBook::loadFromFile() {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {

        contactCount = 0;
        return;
    }


    if (fscanf(file, "%d\n", &contactCount) != 1) {
        contactCount = 0;
        fclose(file);
        return;
    }


    if (contactCount > MAX_CONTACTS) {
        contactCount = MAX_CONTACTS;
    }

    for (int i = 0; i < contactCount; i++) {
        fgets(contacts[i].surname, MAX_STRING_LENGTH, file);

        contacts[i].surname[myStrlen(contacts[i].surname) - 1] = '\0';

        fgets(contacts[i].name, MAX_STRING_LENGTH, file);
        contacts[i].name[myStrlen(contacts[i].name) - 1] = '\0';

        fgets(contacts[i].homePhone, MAX_STRING_LENGTH, file);
        contacts[i].homePhone[myStrlen(contacts[i].homePhone) - 1] = '\0';

        fgets(contacts[i].workPhone, MAX_STRING_LENGTH, file);
        contacts[i].workPhone[myStrlen(contacts[i].workPhone) - 1] = '\0';

        fgets(contacts[i].homeAddress, MAX_STRING_LENGTH, file);
        contacts[i].homeAddress[myStrlen(contacts[i].homeAddress) - 1] = '\0';

        fgets(contacts[i].email, MAX_STRING_LENGTH, file);
        contacts[i].email[myStrlen(contacts[i].email) - 1] = '\0';

        fscanf(file, "%d %d %d\n", &contacts[i].birthDate.day,
            &contacts[i].birthDate.month, &contacts[i].birthDate.year);

        fgets(contacts[i].group, MAX_STRING_LENGTH, file);
        contacts[i].group[myStrlen(contacts[i].group) - 1] = '\0';

        int blacklisted;
        fscanf(file, "%d\n", &blacklisted);
        contacts[i].isBlacklisted = (blacklisted == 1);
    }

    fclose(file);
}
