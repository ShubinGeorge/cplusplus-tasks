#include <iostream>
#include "storage.h"
#include "Hash.h"

PasswordStorage::PasswordStorage(const int size) : storage(size)
{}


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

std::string GetNickPassword(const std::string& nickname)
{
    
    //Хочу здесь обратиться к методу PasswordControl(),
    //чтобы проверить правильность пароля и допусть/не допустить 
    //пользователя к методу,хотя в main() метод работает
    //Не выходит обратиться через bool flag = this->PasswordControl()
    //bool flag = storage.PasswordControl(); тоже не работает
    return 0;
}




