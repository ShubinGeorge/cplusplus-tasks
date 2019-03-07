#include <iostream>
#include <utility>
#include "Hash.h"
#include "storage.h"


int main()
{
    std::pair<std::string, std::string> bascet;
    bascet.second = "qwerty";
    bascet.first = "Egor";

    HashTable example(1000);

    example.Add(bascet);
    std::cout << example.GetHash(bascet) << "\n";
    std::cout << example.GetBasketSize(792) << "\n";

    example.Remove(bascet);
    std::cout << example.GetBasketSize(792) << "\n";

    return 0;
}