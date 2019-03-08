#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <utility>


class HashTable
{
    friend class PasswordStorage;
public:

    HashTable(const int size);

    void Add(const std::pair<std::string, std::string>& new_pair);
    bool Has(const std::string& value) const;
    void Remove(const std::pair<std::string, std::string>& pair);
    int GetHash(const std::string& pair) const;

    int GetHash6(const std::string& string) const;
    const std::vector<std::vector<std::pair<std::string, std::string>>> GetData() const;

    size_t GetBasketSize(const int key) const;

private:
    std::vector<std::vector<std::pair<std::string, std::string>>> data_;
};
