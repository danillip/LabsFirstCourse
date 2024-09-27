//random.cpp
#include "abonent.h"
#include "random.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime> // Для генерации случайных значений
#include <cstdlib> // Для генерации случайных значений

std::vector<std::string> operators = { "900", "901", "902", "903", "904", "905", "906", "907", "908", "909", "910", "911", "912", "913", "914", "915", "916", "917", "918", "919", "920" };
std::vector<std::string> streets = { "Ленина", "Пушкина", "Гагарина", "Советская", "Кирова", "Красная", "Мира" };
std::vector<std::string> maleFirstNames = { "Иван", "Петр", "Александр", "Сергей" };
std::vector<std::string> maleLastNames = { "Иванович", "Петрович", "Александрович", "Сергеевич" };
std::vector<std::string> femaleFirstNames = { "Анна", "Екатерина", "Мария", "Ольга" };
std::vector<std::string> femaleLastNames = { "Ивановна", "Петровна", "Александровна", "Сергеевна" };
std::string generateRandomOperator() {
    int index = rand() % operators.size();
    return operators[index];
}

std::string generateRandomStreet() {
    int index = rand() % streets.size();
    return streets[index];
}

int generateRandomHouseNumber() {
    return 1 + rand() % 100; // Например, от 1 до 100
}

int generateRandomApartmentNumber() {
    return 1 + rand() % 50; // Например, от 1 до 50
}

double generateRandomBalance() {
    return static_cast<double>(rand() % 1000) / 10.0; // Например, от 0.0 до 100.0
}

// Функция для генерации случайного имени в зависимости от пола
std::string generateRandomFirstName(const std::vector<std::string>& firstNames) {
    int index = rand() % firstNames.size();
    return firstNames[index];
}

// Функция для генерации случайной фамилии в зависимости от пола
std::string generateRandomLastName(const std::vector<std::string>& lastNames) {
    int index = rand() % lastNames.size();
    return lastNames[index];
}

std::string generateRandomPhoneNumber() {
    std::string phoneNumber = "+7-"; // Код страны для России

    // Генерируем код оператора (трехзначный)
    phoneNumber += generateRandomOperator();

    phoneNumber += "-";

    // Генерируем номер абонента (семизначный)
    for (int i = 0; i < 7; i++) {
        phoneNumber += std::to_string(rand() % 10);
    }

    return phoneNumber;
}

// Функция для создания случайного абонента с близкими к реальным данными
Abonent createRandomAbonent() {
    Abonent abonent;
    if (rand() % 2 == 0) {
        // Мужской пол
        abonent.name = generateRandomFirstName(maleFirstNames) + " " + generateRandomLastName(maleLastNames);
    }
    else {
        // Женский пол
        abonent.name = generateRandomFirstName(femaleFirstNames) + " " + generateRandomLastName(femaleLastNames);
    }
    abonent.address.street = generateRandomStreet();
    abonent.address.houseNumber = generateRandomHouseNumber();
    abonent.address.apartmentNumber = generateRandomApartmentNumber();
    abonent.phoneNumber = generateRandomPhoneNumber();
    abonent.balance = generateRandomBalance();
    return abonent;
}

void addRandomAbonent(List& head) {
    Abonent randomAbonent = createRandomAbonent();
    addToHead(head, randomAbonent);
}



//abonent.cpp
#include "abonent.h"
#include <iostream>
#include <vector>

void addToHead(List& head, const Abonent& abonent) {
    List newNode = new Node;
    newNode->data = abonent;
    newNode->next = head;
    head = newNode;
}

void printList(const List& head, std::ofstream& outFile) {
    List current = head;
    while (current != nullptr) {
        Abonent abonent = current->data;
        outFile << abonent.name << "\n";
        outFile << abonent.address.street << "\n";
        outFile << abonent.address.houseNumber << "\n";
        outFile << abonent.address.apartmentNumber << "\n";
        outFile << abonent.phoneNumber << "\n";
        outFile << abonent.balance << "\n";
        current = current->next;
    }
}

void clearList(List& head) {
    while (head != nullptr) {
        List temp = head;
        head = head->next;
        delete temp;
    }
}

void readAbonentFromFile(std::ifstream& inFile, Abonent& abonent) {
    getline(inFile, abonent.name);
    getline(inFile, abonent.address.street);
    inFile >> abonent.address.houseNumber;
    inFile >> abonent.address.apartmentNumber;
    inFile.ignore(); // Считываем символ новой строки
    getline(inFile, abonent.phoneNumber);
    inFile >> abonent.balance;
    inFile.ignore(); // Считываем символ новой строки
}

void createListFromFile(List& head, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    Abonent abonent;
    while (!inFile.eof()) {
        readAbonentFromFile(inFile, abonent);
        addToHead(head, abonent);
    }

    inFile.close();
}

void sortByPhoneNumber(List& head) {
    if (head == nullptr || head->next == nullptr) {
        return;  // List is already sorted
    }

    List sortedList = nullptr;
    List current = head;

    while (current != nullptr) {
        List next = current->next;
        if (sortedList == nullptr || current->data.phoneNumber < sortedList->data.phoneNumber) {
            current->next = sortedList;
            sortedList = current;
        }
        else {
            List sortedCurrent = sortedList;
            while (sortedCurrent->next != nullptr && current->data.phoneNumber > sortedCurrent->next->data.phoneNumber) {
                sortedCurrent = sortedCurrent->next;
            }
            current->next = sortedCurrent->next;
            sortedCurrent->next = current;
        }
        current = next;
    }

    head = sortedList;
}

std::string getOperator(const std::string& phoneNumber) {
    if (phoneNumber.length() >= 6) {
        // Извлекаем три цифры после "+7-"
        return phoneNumber.substr(3, 3);
    }
    return "";
}

int countAbonentsByOperator(const List& head, const std::string& operatorPrefix) {
    int count = 0;
    List current = head;
    while (current != nullptr) {
        if (getOperator(current->data.phoneNumber) == operatorPrefix) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void findOperatorWithMostSubscribers(const List& head) {
    std::vector<std::string> operatorPrefixes;
    List current = head;

    while (current != nullptr) {
        std::string operatorPrefix = getOperator(current->data.phoneNumber);
        if (std::find(operatorPrefixes.begin(), operatorPrefixes.end(), operatorPrefix) == operatorPrefixes.end()) {
            operatorPrefixes.push_back(operatorPrefix);
        }
        current = current->next;
    }

    std::string mostSubscribersOperator = "";
    int maxSubscribers = 0;

    for (const std::string& operatorPrefix : operatorPrefixes) {
        int subscribers = countAbonentsByOperator(head, operatorPrefix);
        if (subscribers > maxSubscribers) {
            mostSubscribersOperator = operatorPrefix;
            maxSubscribers = subscribers;
        }
    }

    if (!mostSubscribersOperator.empty()) {
        std::cout << "Оператор с наибольшим количеством абонентов: " << mostSubscribersOperator << std::endl;
        std::cout << "Количество абонентов: " << maxSubscribers << std::endl;
    }
    else {
        std::cout << "Не найдено абонентов." << std::endl;
    }
}

void sortByBalanceAscending(List& head) {
    if (head == nullptr || head->next == nullptr) {
        return;  // Список уже отсортирован
    }

    List sortedList = nullptr;
    List current = head;

    while (current != nullptr) {
        List next = current->next;
        if (sortedList == nullptr || current->data.balance < sortedList->data.balance) {
            current->next = sortedList;
            sortedList = current;
        }
        else {
            List sortedCurrent = sortedList;
            while (sortedCurrent->next != nullptr && current->data.balance > sortedCurrent->next->data.balance) {
                sortedCurrent = sortedCurrent->next;
            }
            current->next = sortedCurrent->next;
            sortedCurrent->next = current;
        }
        current = next;
    }

    head = sortedList;
}

// Функция для ввода абонента с клавиатуры
void inputAbonentFromKeyboard(List& head) {
    Abonent abonent;
    std::cout << "Введите Имя: ";
    std::cin.ignore(); // Очистить буфер ввода перед использованием getline
    std::getline(std::cin, abonent.name);
    std::cout << "Введите улицу: ";
    std::getline(std::cin, abonent.address.street);
    std::cout << "Введите номер дома: ";
    std::cin >> abonent.address.houseNumber;
    std::cout << "Введите номер квартиры: ";
    std::cin >> abonent.address.apartmentNumber;
    std::cout << "Введите номер телефона: ";
    std::cin >> abonent.phoneNumber;
    std::cout << "Введите баланс: ";
    std::cin >> abonent.balance;

    addToHead(head, abonent);
}

// Функция для вывода всех абонентов
void printAllAbonents(const List& head) {
    List current = head;
    while (current != nullptr) {
        Abonent abonent = current->data;
        std::cout << "Имя: " << abonent.name << "\n";
        std::cout << "Улицы: " << abonent.address.street << "\n";
        std::cout << "Номер дома: " << abonent.address.houseNumber << "\n";
        std::cout << "Квартира: " << abonent.address.apartmentNumber << "\n";
        std::cout << "Номер телефона: " << abonent.phoneNumber << "\n";
        std::cout << "Баланс: " << abonent.balance << " Рублей" "\n";
        std::cout << "\n";
        current = current->next;
    }
}

// Функция для сохранения абонентов в файл
void saveAbonentsToFile(const List& head, const std::string& filename) {
    std::ofstream outFile(filename);
    List current = head;
    while (current != nullptr) {
        Abonent abonent = current->data;
        outFile << abonent.name << "\n";
        outFile << abonent.address.street << "\n";
        outFile << abonent.address.houseNumber << "\n";
        outFile << abonent.address.apartmentNumber << "\n";
        outFile << abonent.phoneNumber << "\n";
        outFile << abonent.balance << "\n";
        current = current->next;
    }
    outFile.close();
}

// Функция для загрузки абонентов из файла
void loadAbonentsFromFile(List& head, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    Abonent abonent;
    while (!inFile.eof()) {
        readAbonentFromFile(inFile, abonent);
        addToHead(head, abonent);
    }

    inFile.close();
    }
	
	
	// random.h
#ifndef RANDOM_H
#define RANDOM_H

#include <string>
#include <vector>
#include <iostream>

std::string generateRandomOperator();
std::string generateRandomStreet();
int generateRandomHouseNumber();
int generateRandomApartmentNumber();
double generateRandomBalance();
std::string generateRandomFirstName();
std::string generateRandomLastName();
std::string generateRandomPhoneNumber();

Abonent createRandomAbonent();
void addRandomAbonent(List& head);

#endif


//abonent.h
#ifndef ABONENT_H
#define ABONENT_H

#include <string>
#include <fstream>

struct Address {
    std::string street;
    int houseNumber;
    int apartmentNumber;
};

struct Abonent {
    std::string name;
    Address address;
    std::string phoneNumber;
    double balance;
};

struct Node {
    Abonent data;
    Node* next;
};

typedef Node* List;

void addToHead(List& head, const Abonent& abonent);

void printList(const List& head, std::ofstream& outFile);

void clearList(List& head);

void readAbonentFromFile(std::ifstream& inFile, Abonent& abonent);

void createListFromFile(List& head, const std::string& filename);

void sortByPhoneNumber(List& head);

std::string getOperator(const std::string& phoneNumber);

int countAbonentsByOperator(const List& head, const std::string& operatorPrefix);

void findOperatorWithMostSubscribers(const List& head);

void sortByBalanceAscending(List& head);

void inputAbonentFromKeyboard(List& head);

void printAllAbonents(const List& head);

void saveAbonentsToFile(const List& head, const std::string& filename);

void loadAbonentsFromFile(List& head, const std::string& filename);

#endif // ABONENT_H



//main.cpp
#include <iostream>
#include "abonent.h"
#include "random.h"

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0)); // Инициализация генератора случайных чисел

    List abonentList = nullptr; // Создаем пустой список абонентов

    int choice;
    while (true) {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить случайного абонента\n";
        std::cout << "2. Ввести абонента с клавиатуры\n";
        std::cout << "3. Вывести всех абонентов\n";
        std::cout << "4. Сохранить абонентов в файл\n";
        std::cout << "5. Загрузить абонентов из файла\n";
        std::cout << "6. Найти оператора с наибольшим количеством абонентов\n";
        std::cout << "7. Сортировать абонентов\n"; // Новый пункт меню
        std::cout << "8. Выйти\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addRandomAbonent(abonentList);
            break;
        case 2:
            inputAbonentFromKeyboard(abonentList);
            break;
        case 3:
            printAllAbonents(abonentList);
            break;
        case 4:
            saveAbonentsToFile(abonentList, "abonents.txt");
            break;
        case 5:
            loadAbonentsFromFile(abonentList, "abonents.txt");
            break;
        case 6:
            findOperatorWithMostSubscribers(abonentList);
            break;
        case 7:
            // Выбор параметра сортировки
            int sortChoice;
            std::cout << "Выберите параметр сортировки:\n";
            std::cout << "1. Сортировка по балансу\n";
            std::cout << "2. Сортировка по номеру телефона\n";
            std::cout << "Введите ваш выбор: ";
            std::cin >> sortChoice;

            if (sortChoice == 1) {
                sortByBalanceAscending(abonentList);
                std::cout << "Абоненты отсортированы по балансу от меньшего к большему." << std::endl;
            }
            else if (sortChoice == 2) {
                sortByPhoneNumber(abonentList);
                std::cout << "Абоненты отсортированы по номеру телефона." << std::endl;
            }
            else {
                std::cout << "Неверный выбор сортировки." << std::endl;
            }
            break;
        case 8:
            clearList(abonentList);
            return 0;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, выберите пункт меню.\n";
            break;
        }
    }

    return 0;
}
