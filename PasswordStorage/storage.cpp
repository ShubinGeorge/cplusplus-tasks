#include <iostream>
#include <istream>
#include <ostream>
#include "storage.h"
#include "Hash.h"


PasswordStorage::PasswordStorage(const int size) : storage_(size)
{}


void PasswordStorage::Add(const std::pair<std::string, std::string>& new_pair)
{
    storage_.Add(new_pair);
}


std::string PasswordStorage::GetNickPassword(const std::string& nickname)
{
    if (storage_.Has(nickname) == false)
    {
        return "Sorry, there is no user <" + nickname +  ">. Try again.";
    }

    int key = storage_.GetHash(nickname);
    for (int i = 0; i < storage_.GetData().size(); i++)
    {
        if (storage_.GetData()[key][i].first == nickname)
        {
            
            return "User:" + nickname + "\nPassword:" + storage_.GetData()[key][i].second;
        }        
    }    
}


void PasswordStorage::PrintStorage()
{
    for (int i = 0; i < storage_.GetData().size(); i++)
    {
        if (!storage_.GetData()[i].empty())
        {
            for (int j = 0; j < storage_.GetData()[i].size(); j++)
            {
                std::cout << "User: " << storage_.GetData()[i][j].first
                    << " Password: " << storage_.GetData()[i][j].second << "\n";
            }
        }
    }
}


std::ostream& operator<<(std::ostream& os, const PasswordStorage& storage)
{
    //os << storage.GetData()[0][0].first;
    return os;
}

