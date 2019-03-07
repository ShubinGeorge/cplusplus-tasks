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
    
    //���� ����� ���������� � ������ PasswordControl(),
    //����� ��������� ������������ ������ � �������/�� ��������� 
    //������������ � ������,���� � main() ����� ��������
    //�� ������� ���������� ����� bool flag = this->PasswordControl()
    //bool flag = storage.PasswordControl(); ���� �� ��������
    return 0;
}




