#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>



class HashTable
{
public:
    int GetHash1(const std::string& value) const;
    int GetHash2(const std::string& value) const;
    int GetHash3(const std::string& value) const;
    int GetHash4(const std::string& value) const;
    int GetHash5(const std::string& value) const;
    int GetHash6(const std::string& value) const;

    HashTable(const int size);

    void Add(const std::string& new_string);
    bool Has(const std::string& string) const;
    void Remove(const std::string& string);
    int GetHash(const std::string& string) const;
    const std::vector<std::vector<std::string>>& GetData() const;

    size_t GetBasketSize(const int key) const;

private:
    std::vector<std::vector<std::string>> data_;
};

int GetHash1(const std::string& value);
int GetHash2(const std::string& value);
int GetHash3(const std::string& value);
int GetHash4(const std::string& value);
int GetHash5(const std::string& value);
int GetHash6(const std::string& value);