#include <iostream>
#include <vector>
#include "forest.h"


int main()
{

    Forest forest(9, 9);
    forest.SetValue(4, 4, 10, 0, 1);

    while (1)
    {
        getchar();
        std::cout << forest;
        forest.Update();
    }

    return 0;
}