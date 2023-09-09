#pragma once
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
namespace StaticLib1 {

    class AssociativeArray {
    private:
        std::map<std::string, std::string> data;
        std::vector<std::string> indexes;

    public:
        AssociativeArray();
        AssociativeArray(const std::map<std::string, std::string>& initialData);
        AssociativeArray(const AssociativeArray& other);
        std::string& operator[](const std::string& key);
        std::string& operator[](const int& key);
        AssociativeArray& operator=(const AssociativeArray& other);
        void visualize();
        void saveToFile(const std::string& filename);
        void loadFromFile(const std::string& filename);
        std::string* operator->();
        void operator()(int i, int j, AssociativeArray& a2);
        void removeByKey(const std::string& key);
        void addPair(const std::string& key, const std::string& val);
    };
}
