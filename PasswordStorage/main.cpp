#include <iostream>
#include <utility>
#include "Hash.h"
#include "storage.h"


int main()
{
    std::pair<std::string, std::string> bascet;
    bascet.second = "qwerty";
    bascet.first = "Egor";

    PasswordStorage example(100);
    std::cout << example.PasswordControl() << "\n";

    return 0;
}