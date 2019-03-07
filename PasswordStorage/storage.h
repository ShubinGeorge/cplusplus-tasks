#pragma once
#include "Hash.h"


class PasswordStorage
{
    friend class HashTable;
public:

    PasswordStorage(const int size);
    bool PasswordControl();
    std::string GetNickPassword(const std::string& nickname);

private:
    HashTable storage;
    int password_hash = 1444;
};