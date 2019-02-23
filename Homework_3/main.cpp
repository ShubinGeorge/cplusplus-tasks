#include <iostream>
#include <vector>
#include "matrix.h"


#define ASSERT_EQUAL(x, y)                                         \
    if ((x) != (y))                                                \
    {                                                              \
        std::cerr << "Assertion failed. File: " << __FILE__        \
            << " Line: " << __LINE__ << " "                        \
            << x << " != " << y << " ("                            \
            << #x << " != " << #y << ")" << std::endl;             \
        fails_count++;                                             \
    }


void TestGetHeight()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix matrix1(0, 3);
    Matrix matrix2(5, 4);
    Matrix matrix3(100000, 3);
    
    ASSERT_EQUAL(matrix1.GetHeight(), 0);    
    ASSERT_EQUAL(matrix2.GetHeight(), 5);
    ASSERT_EQUAL(matrix3.GetHeight(), 100000);
    
    if (fails_count == 0)
    {
        std::cerr << "TestHeight: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestHeight fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestGetWidth()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;
    
    Matrix matrix1(3, 0);
    Matrix matrix2(2, 5);
    Matrix matrix3(3, 100000);
    
    ASSERT_EQUAL(matrix1.GetWidth(), 0);
    ASSERT_EQUAL(matrix2.GetWidth(), 5);
    ASSERT_EQUAL(matrix3.GetWidth(), 100000);
    
    if (fails_count == 0)
    {
        std::cerr << "TestGetWidth: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestGetWidth fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestMultiplication()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix matrix0(2, 2);
    Matrix matrix1(2, 2);
    matrix1.SetValue(0, 0, 1);
    matrix1.SetValue(0, 1, 0);
    matrix1.SetValue(1, 0, 0);
    matrix1.SetValue(1, 1, 1);

    Matrix matrix3(1, 1);
    Matrix matrix2(1, 1);
    matrix2.SetValue(0, 0, 1);
 
    Matrix matrix4(2, 2);
    matrix4.SetValue(0, 0, 7);
    matrix4.SetValue(0, 1, 4);
    matrix4.SetValue(1, 0, 5);
    matrix4.SetValue(1, 1, 3);

    Matrix matrix5(2, 2);
    matrix5.SetValue(0, 0, 3);
    matrix5.SetValue(0, 1, -4);
    matrix5.SetValue(1, 0, -5);
    matrix5.SetValue(1, 1, 7);

    Matrix test_1(2, 2);
    Matrix test_2(1, 1);
    Matrix test_3(2, 2);
    Matrix test_4(2, 2);

    test_1 = matrix0 * matrix1;//Домножение на нулевую
    test_2 = matrix2 * matrix3;//Домножение на еденичную
    test_3 = matrix4 * matrix5;//Проверка двух обратных матриц
    test_4 = matrix5 * matrix4;//Проверка тех же матриц, в другом порядке

    ASSERT_EQUAL(test_1, matrix0);
    ASSERT_EQUAL(test_2, matrix3);
    ASSERT_EQUAL(test_3, matrix1);
    ASSERT_EQUAL(test_4, matrix1);

    if (fails_count == 0)
    {
        std::cerr << "TestMultiplication: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestMultiplication fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestTranspose()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix matrix1(2, 2);
    matrix1.SetValue(0, 0, 1);
    matrix1.SetValue(0, 1, 0);
    matrix1.SetValue(1, 0, 0);
    matrix1.SetValue(1, 1, 1);

    Matrix matrix2(1, 1);

    Matrix matrix3(2, 2);
    matrix3.SetValue(0, 0, 7);
    matrix3.SetValue(0, 1, 4);
    matrix3.SetValue(1, 0, 5);
    matrix3.SetValue(1, 1, 3);

    Matrix matrix4(2, 2);
    matrix4.SetValue(0, 0, 7);
    matrix4.SetValue(0, 1, 5);
    matrix4.SetValue(1, 0, 4);
    matrix4.SetValue(1, 1, 3);

    Matrix test_1(2, 2);
    Matrix test_2(1, 1);
    Matrix test_3(2, 2);

    test_1 = matrix1.Transpose();//Транспонируем еденичную 2*2
    test_2 = matrix2.Transpose();//Транспонируем нулевую 1*1
    test_3 = matrix3.Transpose();//Транспонируем произвольную 2*2

    ASSERT_EQUAL(test_1, matrix1);
    ASSERT_EQUAL(test_2, matrix3);
    ASSERT_EQUAL(test_3, matrix4);

    if (fails_count == 0)
    {
        std::cerr << "TestTranspose: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestTranspose fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestGetValue()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix matrix1(2, 2);
    matrix1.SetValue(0, 0, 7);
    matrix1.SetValue(0, 1, 4);
    matrix1.SetValue(1, 0, 5);
    matrix1.SetValue(1, 1, 3);

    ASSERT_EQUAL(matrix1.GetValue(0, 0), 7);
    ASSERT_EQUAL(matrix1.GetValue(0, 1), 4);
    ASSERT_EQUAL(matrix1.GetValue(1, 0), 5);
    ASSERT_EQUAL(matrix1.GetValue(1, 1), 3);

    Matrix matrix2(1, 1);
    ASSERT_EQUAL(matrix2.GetValue(0, 0), 0);

    if (fails_count == 0)
    {
        std::cerr << "TestGetValue: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestGetValue fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestSetValue()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix matrix1(2, 2);
    matrix1.SetValue(0, 0, 1);
    matrix1.SetValue(0, 1, 0);
    matrix1.SetValue(1, 0, 0);
    matrix1.SetValue(1, 1, 1);

    ASSERT_EQUAL(matrix1.GetValue(0, 0), 1);
    ASSERT_EQUAL(matrix1.GetValue(0, 1), 0);
    ASSERT_EQUAL(matrix1.GetValue(1, 0), 0);
    ASSERT_EQUAL(matrix1.GetValue(1, 1), 1);

    Matrix matrix2(1, 1);
    ASSERT_EQUAL(matrix2.GetValue(0, 0), 0);

    Matrix matrix3(1, 1);
    matrix3.SetValue(0, 0, 1000000);
    ASSERT_EQUAL(matrix3.GetValue(0, 0), 1000000);

    if (fails_count == 0)
    {
        std::cerr << "TestSetValue: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestSetValue fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestEqual()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix matrix1(1, 1);
    Matrix matrix2(1, 1);
    Matrix matrix3(2, 2);
    matrix3.SetValue(0, 0, 1000);
    matrix3.SetValue(0, 1, -1000000);
    matrix3.SetValue(1, 0, 0);
    matrix3.SetValue(1, 1, 1);

    Matrix equal_1(1, 1);
    Matrix equal_2(1, 1);
    Matrix equal_3(2, 2);

    equal_1 = matrix1;
    equal_2 = matrix2;
    equal_3 = matrix3;

    bool test_1 = false;
    bool test_2 = false;
    bool test_3 = false;

    if (matrix1 == equal_1)
    {
        test_1 = true;
    }

    if (matrix2 == equal_2)
    {
        test_2 = true;
    }

    if (matrix3 == equal_3)
    {
        test_3 = true;
    }

    ASSERT_EQUAL(test_1, 1);
    ASSERT_EQUAL(test_2, 1);
    ASSERT_EQUAL(test_3, 1);

    if (fails_count == 0)
    {
        std::cerr << "TestEqual: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestEqual fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}



int main()
{

    TestMultiplication();
    TestTranspose();
    TestGetHeight();
    TestGetWidth();
    TestGetValue();
    TestSetValue();
    TestEqual();

    {
        Matrix matrix1(1000, 1000);
        Matrix matrix2(1000, 1000);
        Matrix matrix3 = matrix1 * matrix2;
    }

    return 0;
}

