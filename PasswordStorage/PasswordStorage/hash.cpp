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
    const int key = GetHash(EncodeString(value));
    for (int i = 0; i < data_[key].size(); i++)
    {
        if (DecodeString(data_[key][i].first) == value)
        {
            return true;
        }
    }
    return false;
}


void HashTable::Add(const std::pair<std::string, std::string>& new_pair)
{
    std::pair<std::string, std::string> pair_copy 
	    {EncodeString(new_pair.first), EncodeString(new_pair.second)};

    if (this->Has(pair_copy.first) == 0)
    {
        const int key = GetHash(pair_copy.first);
        data_[key].push_back(pair_copy);
    }
}


int HashTable::GetHash(const std::string& value) const
{
    return GetHashFromString(value) % data_.size();
}


void HashTable::Remove(const std::pair<std::string, std::string>& pair)
{
    if (this->Has(pair.first))
    {
        const int key = GetHash(EncodeString(pair.first));
        for (int i = 0; i < data_[key].size(); i++)
        {
            if (EncodeString(pair.first) == data_[key][i].first)
            {
                data_[key].erase(data_[key].begin() + i);
                break;
            }
        }
    }
    else
    {
        std::cout << "There is no such user" << "\n";
    }
}


const std::vector<std::vector<std::pair<std::string, std::string>>>& HashTable::GetData() const
{
    return data_;
}


std::string EncodeString(const std::string& string_to_encode)
{
    std::string encoded_string = string_to_encode;
    for (int i = 0; i < encoded_string.size(); i++)
    {
        encoded_string[i] += (i + 1);
    }
    return encoded_string;
}


std::string DecodeString(const std::string& string_to_decode)
{
    std::string decoded_string = string_to_decode;
    for (int i = 0; i < decoded_string.size(); i++)
    {
        decoded_string[i] -= (i + 1);
    }
    return decoded_string;
}


int GetHashFromString(const std::string& value)
{
    if (value.size() == 0)
    {
        return 1;
    }

    int hash = value[0];
    for (int i = 1; i < value.size(); i++)
    {
        hash = (hash << 1) ^ value[i];
    }
    return hash;
}
