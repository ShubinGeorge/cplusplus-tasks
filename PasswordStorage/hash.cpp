#include <iostream>
#include <cmath>
#include "Hash.h"


HashTable::HashTable(const int size)
{
    for (int i = 0; i < size; i++)
    {
        std::vector<std::pair<std::string, std::string>> basket;
        data_.push_back(basket);
    }
}


size_t HashTable::GetBasketSize(const int key) const
{
    return data_[key].size();
}


bool HashTable::Has(const std::string& value) const
{
    int key = GetHash(value);
    for (int i = 0; i < data_[key].size(); i++)
    {
        if (data_[key][i].first == value)
        {
            return true;
        }
    }
    return false;
}


void HashTable::Add(const std::pair<std::string, std::string>& new_pair)
{
    if (this->Has(new_pair.first) == 0)
    {
        int key = GetHash(new_pair.first);
        data_[key].push_back(new_pair);
    }
}


int HashTable::GetHash(const std::string& value) const
{
    return GetHash6(value) % data_.size();
}


void HashTable::Remove(const std::pair<std::string, std::string>& pair)
{
    int key = GetHash(pair.first);
    for (int i = 0; i < data_[key].size(); i++)
    {
        if (pair == data_[key][i])
        {
            data_.erase(data_.begin() + i);
            break;
        }
    }
}


const std::vector<std::vector<std::pair<std::string, std::string>>> HashTable::GetData() const
{
    std::vector<std::vector<std::pair<std::string, std::string>>> result;
    for (int i = 0; i < data_.size(); i++)
    {
        result.push_back(data_[i]);
    }
    return result;
}
