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


bool HashTable::Has(const std::pair<std::string, std::string>& pair) const
{
    int key = GetHash(pair);
    for (int i = 0; i < data_[key].size(); i++)
    {
        if (data_[key][i].first == pair.first)
        {
            return true;
        }
    }
    return false;
}


void HashTable::Add(const std::pair<std::string, std::string>& new_pair)
{
    if (this->Has(new_pair) == 0)
    {
        int key = GetHash(new_pair);
        data_[key].push_back(new_pair);
    }
}


int HashTable::GetHash(const std::pair<std::string, std::string>& pair) const
{
    return GetHash6(pair.first) % data_.size();
}


int HashTable::GetHash6(const std::string& value) const
{
    if (value.size() == 0)
    {
        return 1;
    }
    else
    {
        int hash = value[0];
        for (int i = 1; i < value.size(); i++)
        {
            hash = (hash << 1) ^ value[i];
        }
        return hash;
    }
}


void HashTable::Remove(const std::pair<std::string, std::string>& pair)
{
    int key = GetHash(pair);
    for (int i = 0; i < data_[key].size(); i++)
    {
        if (pair == data_[key][i])
        {
            data_.erase(data_.begin() + i);
            break;
        }
    }
}



