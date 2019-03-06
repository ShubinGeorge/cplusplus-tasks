#include <iostream>
#include <vector>
#include <string>
#include "Hash.h"
#include <cmath>
#include <fstream>


int main()
{
    const int table_size = 1013;
    HashTable example_1(table_size);

    std::ifstream in_stream("cano.txt");
    for (std::string word; in_stream >> word; )
    {
        example_1.Add(word);
    }

    std::ofstream fout("hash_6.txt");

    for (int i = 0; i < table_size; i++)
    {
        fout << example_1.GetBasketSize(i) << "\n";
    }

    return 0;
}