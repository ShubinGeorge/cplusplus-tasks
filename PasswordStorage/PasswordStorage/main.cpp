#include <iostream>
#include <utility>
#include "Hash.h"
#include "storage.h"

//Пароль Open your secret

void CheckPassword(PasswordStorage storage)
{
    std::cout << "Please, enter password: ";
    std::string user_password;
    std::getline(std::cin, user_password);
    if (GetHashFromString(user_password) != storage.GetPasswordHash())
    {
        std::cout << "Incorrect password, try again" << "\n";
        CheckPassword(storage);
    }
}


int main()
{

    PasswordStorage example_1(10);

    std::pair<std::string, std::string> user_1;
    std::pair<std::string, std::string> user_2;
    std::pair<std::string, std::string> user_3;
    std::pair<std::string, std::string> user_4;
    std::pair<std::string, std::string> user_5;
    std::pair<std::string, std::string> user_6;
    std::pair<std::string, std::string> user_7;
    std::pair<std::string, std::string> user_8;
    std::pair<std::string, std::string> user_9;
    std::pair<std::string, std::string> user_10;

    user_1.first = "Lam";
    user_1.second = "qwerty";

    user_2.first = "Paul";
    user_2.second = "qwerty123";

    user_3.first = "Phill";
    user_3.second = "password";

    user_4.first = "Lama";
    user_4.second = "nsc_cronus";

    user_5.first = "Tom";
    user_5.second = "Yooou!";

    user_6.first = "Leo";
    user_6.second = "Tre_123_321";

    user_7.first = "Pavel";
    user_7.second = "RedPrice41";

    user_8.first = "Sam";
    user_8.second = "Tarli";

    user_9.first = "Jon";
    user_9.second = "Snow";

    user_10.first = "Tirion";
    user_10.second = "Lanister";


    example_1.Add(user_1);
    example_1.Add(user_2);
    example_1.Add(user_3);
    example_1.Add(user_4);
    example_1.Add(user_5);
    example_1.Add(user_6);
    example_1.Add(user_7);
    example_1.Add(user_8);
    example_1.Add(user_9);
    example_1.Add(user_10);


    CheckPassword(example_1);
    std::cout << "You can use comands:" << "\n"
        << "1)print storage: print all database content" << "\n"
        << "2)get password: print Nickname password" << "\n"
        << "3)change password: change secret password" << "\n"
        << "4)exit: close programm" << "\n";

    while(1)
    {
        std::string user_command;
        std::getline(std::cin, user_command);

        if (user_command == "exit")
        {
            exit(0);
        }
		
        if (user_command == "print storage")
        {
            std::cout << example_1;
        }
		
        if (user_command == "change password")
        {
            std::cout << "Enter previous password: ";
            std::string previous_password;
            std::getline(std::cin, previous_password);
		
            if (GetHashFromString(previous_password) == example_1.GetPasswordHash())
            {
                std::cout << "Enter new password: ";
                std::string new_password;
                std::getline(std::cin, new_password);
                example_1.ChangePassword(new_password);
                CheckPassword(example_1);
            }
            else
            {
                std::cout << "Sorry, incorrect password" << "\n";
            }
        }

        if (user_command == "get password")
        {
            std::cout << "Enter nickname: ";
            std::string nickname;
            std::getline(std::cin, nickname);

            if (example_1.Has(nickname))
            {
                std::cout << example_1.GetNickPassword(nickname) << "\n";
            }
            else
            {
                std::cout << "Sorry, there are no user with such nickname" << "\n";		  
            }
        }
    }
		   
    return 0;
}




