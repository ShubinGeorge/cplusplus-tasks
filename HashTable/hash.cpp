#include <iostream>
#include <cmath>
#include "Hash.h"


HashTable::HashTable(const int size)
{
    for (int i = 0; i < size; i++)
    {
        std::vector<std::string> basket;
        data_.push_back(basket);
    }
}


void HashTable::Add(const std::string& new_string)
{
    if (this->Has(new_string) == 0)
    {
        int key = GetHash(new_string);
        data_[key].push_back(new_string);
    }
}


void HashTable::Remove(const std::string& value)
{
    int key = GetHash(value);
    for (int i = 0; i < data_[key].size(); i++)
    {
        if (value == data_[key][i])
        {
            data_.erase(data_.begin() + i);
            break;
        }
    }
}


int HashTable::GetHash(const std::string& value) const
{   
    return GetHash6(value) % data_.size();
}


bool HashTable::Has(const std::string& value) const
{
    int key = GetHash(value);
    for (int i = 0; i < data_[key].size(); i++)
    {
        if (data_[key][i] == value)
        {
            return true;
        }
    }
    return false;
}


size_t HashTable::GetBasketSize(const int key) const
{
    return data_[key].size();
}


const std::vector<std::vector<std::string>>& HashTable::GetData() const
{
    std::vector<std::vector<std::string>> result;
    for (int i = 0; i < data_.size(); i++)
    {
        result.push_back(data_[i]);
    }
    return result;   
}


int HashTable::GetHash1(const std::string& value) const
{
    return 1;
}


int HashTable::GetHash2(const std::string& value) const
{
    return value[0] - 0;
}


int HashTable::GetHash3(const std::string& value) const
{
    return value.size();
}


int HashTable::GetHash4(const std::string& value) const
{
    int hash = 0;
    for (int i = 0; i < value.size(); i++)
    {
        hash += (value[i] - 0);
    }
    return hash;
}


int HashTable::GetHash5(const std::string& value) const
{
    int hash = 0;
    for (int i = 0; i < value.size(); i++)
    {
        hash += (value[i] << 2) * 179;
    }
    return hash;
}


int HashTable::GetHash6(const std::string& value) const
{
    if(value.size() == 0)
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





