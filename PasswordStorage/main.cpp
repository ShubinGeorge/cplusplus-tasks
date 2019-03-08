#include <iostream>
#include <utility>
#include "Hash.h"
#include "storage.h"

//please,open
/*
std::cout << "Please, input password: ";
std::string user_password;
std::getline(std::cin, user_password);
*/


int main()
{
    std::pair<std::string, std::string> user_1;
    std::pair<std::string, std::string> user_3;
    std::pair<std::string, std::string> user_2;

    user_1.first = "Lam";
    user_1.second = "qwerty";

    user_2.first = "Paul";
    user_2.second = "qwerty123";

    user_3.first = "Phill";
    user_3.second = "password";

    PasswordStorage example_1(10);
    example_1.Add(user_1);
    example_1.Add(user_2);
    example_1.Add(user_3);
  
    example_1.PrintStorage();
   
    //std::cout << example_1.GetNickPassword("Lam") << "\n";
    //std::cout << example_1.GetNickPassword("Phll") << "\n";
    //std::cout << example_1.GetNickPassword("Paul") << "\n";

    return 0;
}