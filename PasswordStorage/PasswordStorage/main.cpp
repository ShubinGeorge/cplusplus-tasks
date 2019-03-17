#include <iostream>
#include <utility>
#include "Hash.h"
#include "storage.h"


bool CheckPassword(PasswordStorage storage)
{
    std::cout << "Please, enter password: ";
    std::string user_password;
    std::getline(std::cin, user_password);
    if (GetHashFromString(user_password) == storage.GetPasswordHash())
    {
        if (GetHashFromString(user_password) != storage.GetPasswordHash())
        {
            std::cout << "It seems somebody tried to patch program)" << "\n";
            exit(0);
        }
        return 1;
    }
    else
    {
        return 0;
    }
}


int main()
{
    PasswordStorage example_1(10);

    std::pair<std::string, std::string> user_1 = {"Lam" , "qwerty"};
    std::pair<std::string, std::string> user_2 = { "Paul", "qwerty123" };
    std::pair<std::string, std::string> user_3 = {"Phill", " password"};
    std::pair<std::string, std::string> user_4 = {"Lama", "nwc_cronus"};
    std::pair<std::string, std::string> user_5 = {"Tom", "Youuuu"};
    std::pair<std::string, std::string> user_6 = {"Leo", "Tre_123_321"};
    std::pair<std::string, std::string> user_7 = {"Pavel", "RedPrice41"};
    std::pair<std::string, std::string> user_8 = {"Sam", "Tarli"};
    std::pair<std::string, std::string> user_9 = {"Jon", "Snow"};
    std::pair<std::string, std::string> user_10 = {"Tirion", "Lanister"};

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

	
    const int max_attempts_number = 2;
    bool access = 0;
    for (int i = 0; i < max_attempts_number; i++)
    {
        access = CheckPassword(example_1);
        if (access == 1)
        {
            if (access != 1)
            {
                std::cout << "It seems somebody tried to patch program)" << "\n";
                return 1;
            }
            break;
        }

        if (i == max_attempts_number - 1 && access != 1)
        {
            if (access == 1)
            {
                std::cout << "It seems somebody tried to patch program)" << "\n";
                return 1;
            }
            return 1;
        }

        std::cout << "Incorrect password, try again" << "\n";
    }

    std::cout << "You can use comands:" << "\n"
        << "1)print storage: print all database content" << "\n"
        << "2)get password: print Nickname password" << "\n"
        << "3)change password: change secret password" << "\n"
        << "4)exit: close program" << "\n";
	
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
