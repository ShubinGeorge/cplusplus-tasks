#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <utility>

std::string EncodeString(const std::string& string_to_encode);
std::string DecodeString(const std::string& string_to_decode);
int GetHashFromString(const std::string& value);


class HashTable
{
public:

    HashTable(const int size);

    void Add(const std::pair<std::string, std::string>& new_pair);
    void Remove(const std::pair<std::string, std::string>& pair);
    bool Has(const std::string& value) const;
    int GetHash(const std::string& pair) const;
    size_t GetBasketSize(const int key) const;

    const std::vector<std::vector<std::pair<std::string, std::string>>>& GetData() const;

private:
    std::vector<std::vector<std::pair<std::string, std::string>>> data_;
};
