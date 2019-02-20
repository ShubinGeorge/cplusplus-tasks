#include <iostream>
#include <vector>

#include "forest.h"

struct Tree
{
    size_t health_ = 5;
    size_t current_state_ = 0;
    bool indicator_ = false;
};

int main()
{

    Tree tree;
    Forest matrix1(9, 9);

    matrix1.SetValue(4, 4, 5, 1);

    while (1)
    {
        getchar();
        std::cout << matrix1 << "\n";
        matrix1.Update();


    }

    return 0;
}


