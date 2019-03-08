#pragma once
#include "Hash.h"
#include <istream>
#include <ostream>


class PasswordStorage
{

   friend std::ostream& operator<<(std::ostream& os, const PasswordStorage& storage);
   friend class HashTable;
public:

    PasswordStorage(const int size);
    std::string GetNickPassword(const std::string& nickname);
    void Add(const std::pair<std::string, std::string>& new_pair);
    void PrintStorage();

private:
    HashTable storage_;
    int password_hash = 89404;
};
std::ostream& operator<<(std::ostream& os, const PasswordStorage& storage);