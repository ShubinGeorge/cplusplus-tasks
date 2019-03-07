#pragma once
#include "Hash.h"


class PasswordStorage
{
    //friend class HashTable;
public:
    PasswordStorage(const int size);
    bool PasswordControl();

private:
    HashTable storage;
    int password_hash;
};