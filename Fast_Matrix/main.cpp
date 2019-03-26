#include <iostream>
#include <vector>
#include "matrix.h"


int main()
{
    {
        Matrix matrix1(1000, 1000);
        Matrix matrix2(1000, 1000);
        Matrix matrix3 = matrix1 * matrix2;
    }

    return 0;
}

