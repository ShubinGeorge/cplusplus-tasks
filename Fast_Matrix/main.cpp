#include <iostream>
#include <vector>
#include "matrix.h"


int main()
{

    std::vector<int> line_1 = {1, 1, 1, 1};
    std::vector<int> line_2 = {1, 1, 1, 1};
    Matrix matrix_1(4, 4);
    Matrix matrix_2(4, 4);
	
    for (int i = 0; i < line_1.size(); i++)
    {
        for (int j = 0; j < line_1.size(); j++)
        {
            matrix_1.SetValue(i, j, line_1[i]);
        }
    }
    std::cout << matrix_1 << "\n";

    for (int i = 0; i < line_2.size(); i++)
    {
        for (int j = 0; j < line_2.size(); j++)  
        {
            matrix_2.SetValue(i, j, line_2[i]);
        }
    }
    std::cout << matrix_2 << "\n";
    std::cout << matrix_1 + matrix_2 << "\n";
    std::cout << matrix_1.TmpMultiplication(matrix_2, 0, 2) << "\n";

    std::cout << matrix_1 * matrix_2 << "\n";
    /*
    {
        Matrix matrix1(1000, 1000);
        Matrix matrix2(1000, 1000);
        Matrix matrix3 = matrix1 * matrix2;
    }
	*/
    return 0;
}

