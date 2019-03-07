#include <iostream>
#include "storage.h"
#include "Hash.h"


PasswordStorage::PasswordStorage(const int size)
{

}

bool PasswordStorage::PasswordControl()
{
    std::cout << "Please, input password: ";
    std::string user_password;
    std::getline(std::cin, user_password);
    
    if (storage.GetHash6(user_password) == password_hash)
    {
        return true;
    }
    return false;
}
