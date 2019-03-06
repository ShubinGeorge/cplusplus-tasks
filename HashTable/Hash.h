#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>



class HashTable
{
    friend int GetHash1(const std::string& value);
    friend int GetHash2(const std::string& value);
    friend int GetHash3(const std::string& value);
    friend int GetHash4(const std::string& value);
    friend int GetHash5(const std::string& value);
    friend int GetHash6(const std::string& value);

public:

    HashTable(const int size);

    void Add(const std::string& new_string);
    bool Has(const std::string& string) const;
    void Remove(const std::string& string); // удаляет строку из корзины, если такая имеется
    int GetHash(const std::string& string) const;
    std::vector<std::vector<std::string>> GetData() const;

    int GetBasketSize(const int key) const;

private:
    std::vector<std::vector<std::string>> data_;
};

int GetHash1(const std::string& value);
int GetHash2(const std::string& value);
int GetHash3(const std::string& value);
int GetHash4(const std::string& value);
int GetHash5(const std::string& value);
int GetHash6(const std::string& value);