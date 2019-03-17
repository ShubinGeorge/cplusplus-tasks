#pragma once
#include "Hash.h"
#include <istream>
#include <ostream>


class PasswordStorage
{

   friend std::ostream& operator<<(std::ostream& os, const PasswordStorage& storage);

public:

    PasswordStorage(const int size);
    std::string GetNickPassword(const std::string& nickname);
    void Add(const std::pair<std::string, std::string>& new_pair);
    int GetPasswordHash();
    void ChangePassword(const std::string& new_password);
    bool Has(const std::string& value) const;
    void Remove(const std::pair<std::string, std::string>& pair);

private:
    HashTable storage_;
    int password_hash = 3257438;
};
std::ostream& operator<<(std::ostream& os, const PasswordStorage& storage);