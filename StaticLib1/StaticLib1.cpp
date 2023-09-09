// StaticLib1.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include "StaticLib1.h"
namespace StaticLib1 {
    AssociativeArray::AssociativeArray() {}

    // Конструктор з параметрами для ініціалізації
    AssociativeArray::AssociativeArray(const std::map<std::string, std::string>& initialData) {
        for (const auto& pair : initialData) {
            data[pair.first] = pair.second;
            indexes.push_back(pair.first);
        }
    }

    // Конструктор копіювання
    AssociativeArray::AssociativeArray(const AssociativeArray& other) {
        data = other.data;
        indexes = other.indexes;
    }

    // Перевантаження оператору []
    std::string& AssociativeArray::operator[](const std::string& key) {
        return data[key];
    }
    // Перевантаження оператору []
    std::string& AssociativeArray::operator[](const int& key) {
        return data[indexes[key]];
    }

    // Перевантаження оператору = (присвоєння)
    AssociativeArray& AssociativeArray::operator=(const AssociativeArray& other) {
        if (this == &other) {
            return *this;
        }
        data = other.data;
        indexes = other.indexes;
        return *this;
    }


    // Метод для візуалізації
    void AssociativeArray::visualize() {
        for (const auto& pair : data) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
    // Метод для збереження на диск
    void AssociativeArray::saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& pair : data) {
                file << pair.first << "," << pair.second << std::endl;
            }
            file.close();
            std::cout << "Дані збережено в файл " << filename << std::endl;
        }
        else {
            std::cerr << "Помилка відкриття файлу для збереження" << std::endl;
        }
    }

    // Метод для відновлення з диску
    void AssociativeArray::loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            data.clear(); // Очистимо поточні дані перед завантаженням нових
            std::string line;
            while (std::getline(file, line)) {
                size_t delimiterPos = line.find(",");
                if (delimiterPos != std::string::npos) {
                    std::string key = line.substr(0, delimiterPos);
                    std::string value = line.substr(delimiterPos + 1);
                    data[key] = value;
                    indexes.push_back(key);
                }
            }
            file.close();
            std::cout << "Дані відновлено з файлу " << filename << std::endl;
        }
        else {
            std::cerr << "Помилка відкриття файлу для завантаження" << std::endl;
        }
    }

    // "Розумний доступ" за ключем
    std::string* AssociativeArray::operator->() {
        // Ми можемо повернути вказівник на поточний об'єкт, наприклад, перший елемент
        // асоціативного масиву
        if (!data.empty()) {
            return &data.begin()->second;
        }
        else {
            return nullptr;
        }
    }

    // Перевантаження оператору ()
    void AssociativeArray::operator()(int i, int j, AssociativeArray& a2) {
        if (i < 0 || i >= indexes.size() ||  j > a2.indexes.size()) {
            std::cerr << "Помилка: i або j виходять за межі" << std::endl;
            return;
        }

        std::map<std::string, std::string> newData;
        std::vector<std::string> newIndexes;

        // Копіюємо елементи з a1 до і-1 у нову мапу та вектор
        for (int k = 0; k < i; ++k) {
            const std::string& key = indexes[k];
            newData[key] = data[key];
            newIndexes.push_back(key);
        }

        // Копіюємо j елементів з a2 у нову мапу та вектор
        for (int k = 0; k < j; ++k) {
            const std::string& key = a2.indexes[k];
            newData[key] = a2.data[key];
            newIndexes.push_back(key);
        }

        // Оновлюємо дані та indexes масиву a1
        data = newData;
        indexes = newIndexes;
    }

    void AssociativeArray::removeByKey(const std::string& key) {
        auto it = data.find(key);
        if (it != data.end()) {
            // Знаходимо позицію елементу в векторі indexes
            std::string t = it->first;
            auto indexIt = std::find(indexes.begin(), indexes.end(), t);

            // Видаляємо елемент із мапи та вектора indexes
            data.erase(it);
            if (indexIt != indexes.end()) {
                indexes.erase(indexIt);
            }
            else {
                std::cerr << "Помилка: не вдалося знайти елемент в indexes" << std::endl;
            }
        }
        else {
            std::cerr << "Помилка: ключ не знайдено" << std::endl;
        }
    }
    void AssociativeArray::addPair(const std::string& key, const std::string& val) {
        auto it = data.find(key);

        if (it != data.end()) {
            data[key] = val;
        }
        else {
            data[key] = val;
            indexes.push_back(key);
        }
    }
}
