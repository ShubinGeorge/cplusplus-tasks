#include <iostream>
#include <istream>
#include <ostream>
#include "storage.h"
#include "Hash.h"


PasswordStorage::PasswordStorage(const int size) : storage_(size)
{}


bool PasswordStorage::Has(const std::string& value) const
{
    return storage_.Has(value);
}


void PasswordStorage::Remove(const std::pair<std::string, std::string>& pair)
{
     storage_.Remove(pair);
}

int PasswordStorage::GetPasswordHash()
{
    return password_hash;
}


void PasswordStorage::ChangePassword(const std::string& new_password)
{
    this->password_hash = GetHashFromString(new_password);
}


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

    const int key = storage_.GetHash(EncodeString(nickname));
    for (int i = 0; i < storage_.GetData()[key].size(); i++)
    {
        if (storage_.GetData()[key][i].first == EncodeString(nickname))
        {        
            return "User:" + nickname + " Password:" + DecodeString(storage_.GetData()[key][i].second);
        }        
    }    
}


std::ostream& operator<<(std::ostream& os, const PasswordStorage& storage)
{
    for (int i = 0; i < storage.storage_.GetData().size(); i++)
    {
        if (!storage.storage_.GetData()[i].empty())
        {
            for (int j = 0; j < storage.storage_.GetData()[i].size(); j++)
            {
                os << "User: " << DecodeString(storage.storage_.GetData()[i][j].first)
                    << " Password: " << DecodeString(storage.storage_.GetData()[i][j].second) << "\n";
            }
        }
    }
    return os;
}
