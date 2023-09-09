#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "StaticLib1.h"


using namespace StaticLib1;
struct NamedAssociativeArray {
    std::string name;
    AssociativeArray obj;
};

int main() {
    std::vector<NamedAssociativeArray> objects;  // Створення вектора іменованих об'єктів AssociativeArray

    int choice;
    do {
        std::cout << "Оберіть операцію:" << std::endl;
        std::cout << "1. Створити об'єкт класу AssociativeArray" << std::endl;
        std::cout << "2. Ввести об'єкт на диск" << std::endl;
        std::cout << "3. Вивести об'єкт з диска" << std::endl;
        std::cout << "4. Візуалізувати об'єкт" << std::endl;
        std::cout << "5. Вивести список наявних об'єктів" << std::endl;
        std::cout << "6. Видалити об'єкт за номером" << std::endl;
        std::cout << "7. Виконати операції над об'єктом" << std::endl;
        std::cout << "8. Вийти" << std::endl;
        std::cout << "Ваш вибір: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // Створення нового об'єкту іменованого класу AssociativeArray
            NamedAssociativeArray newNamedObj;
            std::cout << "Введіть ім'я для об'єкта: ";
            std::cin >> newNamedObj.name;

            // Діалог для введення ключів та значень
            std::string key, value;
            char continueAdding;

            do {
                std::cout << "Введіть ключ: ";
                std::cin >> key;
                std::cout << "Введіть значення: ";
                std::cin >> value;

                newNamedObj.obj.addPair(key, value);

                std::cout << "Продовжити додавання? (y/n): ";
                std::cin >> continueAdding;
            } while (continueAdding == 'y' || continueAdding == 'Y');

            objects.push_back(newNamedObj);
            std::cout << "Об'єкт створено та заповнено." << std::endl;
            break;
        }
        case 2: {
            // Ввід об'єкту на диск
            int index;
            std::cout << "Введіть індекс об'єкта для збереження: ";
            std::cin >> index;
            if (index >= 0 && index < objects.size()) {
                std::string filename;
                std::cout << "Введіть ім'я файлу для збереження: ";
                std::cin >> filename;
                objects[index].obj.saveToFile(filename);
            }
            else {
                std::cout << "Неправильний індекс об'єкта." << std::endl;
            }
            break;
        }
        case 3: {
            // Вивід об'єкту з диска і додавання його в кінець вектора
            std::string filename;
            std::cout << "Введіть назву файла для вивантаження об'єкта: ";
            std::cin >> filename;
            AssociativeArray newObj;
            newObj.loadFromFile(filename);

            NamedAssociativeArray newNamedObj;
            std::cout << "Введіть ім'я для об'єкта: ";
            std::cin >> newNamedObj.name;
            newNamedObj.obj = newObj;

            objects.push_back(newNamedObj);
            std::cout << "Об'єкт завантажено з файла та додано в список." << std::endl;
            break;
        }
        case 4: {
            // Візуалізація об'єкту
            int index;
            std::cout << "Введіть індекс об'єкта для візуалізації: ";
            std::cin >> index;
            if (index >= 0 && index < objects.size()) {
                std::cout << "Ім'я об'єкта: " << objects[index].name << std::endl;
                objects[index].obj.visualize();
            }
            else {
                std::cout << "Неправильний індекс об'єкта." << std::endl;
            }
            break;
        }
        case 5: {
            // Виведення списку наявних об'єктів
            std::cout << "Список наявних об'єктів:" << std::endl;
            for (int i = 0; i < objects.size(); ++i) {
                std::cout << i << ". " << objects[i].name << std::endl;
            }
            break;
        }
        case 6: {
            // Видалення об'єкта за номером
            int index;
            std::cout << "Введіть номер об'єкта для видалення: ";
            std::cin >> index;
            if (index >= 0 && index < objects.size()) {
                objects.erase(objects.begin() + index);
                std::cout << "Об'єкт видалено." << std::endl;
            }
            else {
                std::cout << "Неправильний номер об'єкта." << std::endl;
            }
            break;
        }
        case 7: {
            // Виконання операцій над об'єктами
            int objIndex;
            std::cout << "Введіть індекс об'єкта для виконання операцій: ";
            std::cin >> objIndex;
            if (objIndex >= 0 && objIndex < objects.size()) {
                AssociativeArray& obj = objects[objIndex].obj;
                int operation;
                std::cout << "Оберіть операцію:" << std::endl;
                std::cout << "1. Копіювання об'єкта" << std::endl;
                std::cout << "2. Отримання значення по ключу" << std::endl;
                std::cout << "3. Отримання значення по індексу" << std::endl;
                std::cout << "4. Операція перевантаження ()" << std::endl;
                std::cout << "Ваш вибір: ";
                std::cin >> operation;

                switch (operation) {
                case 1: {
                    // Копіювання об'єкта
                    AssociativeArray copiedObj = obj;
                    std::string newName;
                    std::cout << "Введіть ім'я для копії об'єкта: ";
                    std::cin >> newName;
                    objects.push_back({ newName, copiedObj });
                    std::cout << "Об'єкт скопійовано та додано в список." << std::endl;
                    break;
                }
                case 2: {
                    // Отримання значення по ключу
                    std::string key;
                    std::cout << "Введіть ключ: ";
                    std::cin >> key;
                    std::string value = obj[key];
                    std::cout << "Значення для ключа \"" << key << "\": " << value << std::endl;
                    break;
                }
                case 3: {
                    // Отримання значення по індексу
                    int index;
                    std::cout << "Введіть індекс: ";
                    std::cin >> index;
                    std::string value = obj[index];
                    std::cout << "Значення за індексом " << index << ": " << value << std::endl;
                    break;
                }
                case 4: {
                    // Операція перевантаження ()
                    int obj2Index;
                    std::cout << "Виберіть інший об'єкт для операції (за номером): ";
                    std::cin >> obj2Index;
                    if (obj2Index >= 0 && obj2Index < objects.size() && objIndex != obj2Index) {
                        AssociativeArray& obj2 = objects[obj2Index].obj;
                        int i, j = 0;
                        std::cout << "Введіть i: ";
                        std::cin >> i;

                        std::cout << "Введіть j: ";
                        std::cin >> j;
                        obj(i, j, obj2);
                        std::cout << "Операція виконана." << std::endl;
                    }
                    else {
                        std::cout << "Неправильний номер об'єкта." << std::endl;
                    }
                    break;
                }
                default: {
                    std::cout << "Неправильний вибір операції. Спробуйте ще раз." << std::endl;
                    break;
                }
                }
            }
            else {
                std::cout << "Неправильний індекс об'єкта." << std::endl;
            }
            break;
        }
        case 8: {
            // Вихід з програми
            std::cout << "Дякуємо за використання програми." << std::endl;
            break;
        }

        default: {
            std::cout << "Неправильний вибір операції. Спробуйте ще раз." << std::endl;
            break;
        }
        }
    } while (choice != 8);

    return 0;
}