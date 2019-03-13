#include "calculator.h"
#include "assert_calculator.h"
#include <iostream>
#include <cassert>


#define ASSERT_EQUAL(x, y)                                         \
    if ((x) != (y))                                                \
    {                                                              \
        std::cerr << "Assertion failed. File: " << __FILE__        \
            << " Line: " << __LINE__ << " "                        \
            << x << " != " << y << " ("                            \
            << #x << " != " << #y << ")" << std::endl;             \
        fails_count++;                                             \
    }


void TestSum()
{
	std::cerr << "------------------";
	int fails_count = 0;
	Calculator calc;
	ASSERT_EQUAL(calc.Sum(2, 3), 5);
	ASSERT_EQUAL(calc.Sum(3, 2), 5);
	ASSERT_EQUAL(calc.Sum(-4, -9), -13);
	ASSERT_EQUAL(calc.Sum(-9, -4), -13);
	ASSERT_EQUAL(calc.Sum(8, 0), 8);
	ASSERT_EQUAL(calc.Sum(0, 20), 20);
	ASSERT_EQUAL(calc.Sum(-9, 0), -9);
	ASSERT_EQUAL(calc.Sum(-20, 7), -13);
	ASSERT_EQUAL(calc.Sum(50, -11), 39);
	ASSERT_EQUAL(calc.Sum(100000, 23456), 123456);
	ASSERT_EQUAL(calc.Sum(-99999, 100000), 1);
	ASSERT_EQUAL(calc.Sum(3, -3), 0);
		
	if (fails_count == 0)
	{
		std::cerr << "TestSum: OK" << std::endl;
	}
	else
	{
		std::cerr << "TestSum, fails_count = " << fails_count << std::endl;
	}
	std::cerr << "------------------" << std::endl;

}

void TestDef()
{
	std::cerr << "------------------";
	int fails_count = 0;
	Calculator calc;
	ASSERT_EQUAL(calc.Def(10, 6), 4);
	ASSERT_EQUAL(calc.Def(10, -9), 19);
	ASSERT_EQUAL(calc.Def(20, 50), -30);
	ASSERT_EQUAL(calc.Def(-18, 1), -19);
	ASSERT_EQUAL(calc.Def(-53, -20), -33);
	ASSERT_EQUAL(calc.Def(-11, -20), 9);
	ASSERT_EQUAL(calc.Def(100, 100), 0);
	ASSERT_EQUAL(calc.Def(-2555, -2555), 0);
	ASSERT_EQUAL(calc.Def(70, 0), 70);
	ASSERT_EQUAL(calc.Def(1000000, 1000001), -1);
	ASSERT_EQUAL(calc.Def(200000, 1), 199999);

	if (fails_count == 0)
	{
		std::cerr << "TestDef: OK" << std::endl;
	}
	else
	{
		std::cerr << "TestDef, fails_count = " << fails_count << std::endl;
	}
	std::cerr << "------------------" << std::endl;

}

void TestMultiplicattion()
{
	std::cerr << "------------------";
	int fails_count = 0;
	Calculator calc;
	ASSERT_EQUAL(calc.Multiplicattion(2, 6), 12);
	ASSERT_EQUAL(calc.Multiplicattion(6, 2), 12);
	ASSERT_EQUAL(calc.Multiplicattion(15, 1), 15); 
	ASSERT_EQUAL(calc.Multiplicattion(2, -11), -22);
	ASSERT_EQUAL(calc.Multiplicattion(-8, 10), -80);
	ASSERT_EQUAL(calc.Multiplicattion(-15, -4), 60);
	ASSERT_EQUAL(calc.Multiplicattion(0, 26), 0);
	ASSERT_EQUAL(calc.Multiplicattion(178, 2255), 401390);
	ASSERT_EQUAL(calc.Multiplicattion(-17800, 256), -4556800);

	if (fails_count == 0)
	{
		std::cerr << "TestMultiplicattion: OK" << std::endl;
	}
	else
	{
		std::cerr << "TestGCD, fails_count = " << fails_count << std::endl;
	}
	std::cerr << "------------------" << std::endl;

}

void TestDivision()
{
	std::cerr << "------------------";
	int fails_count = 0;
	Calculator calc;
	ASSERT_EQUAL(calc.Division(10, 2), 5);
	ASSERT_EQUAL(calc.Division(-80, 4), -20);
	ASSERT_EQUAL(calc.Division(100, -50), -2);
	ASSERT_EQUAL(calc.Division(-48, -4), 12);
	ASSERT_EQUAL(calc.Division(45, 1), 45);
	ASSERT_EQUAL(calc.Division(45, 45), 1);
	ASSERT_EQUAL(calc.Division(0, 7), 0);
	ASSERT_EQUAL(calc.Division(1, 3), 0);
	ASSERT_EQUAL(calc.Division(5, 0), 0);

        if (fails_count == 0)
	{
		std::cerr << "TestDivision: OK" << std::endl;
	}
	else
	{
		std::cerr << "TestDivision, fails_count = " << fails_count << std::endl;
	}
	std::cerr << "------------------" << std::endl;

}

void TestPow ()
{
	std::cerr << "------------------";
	int fails_count = 0;
	Calculator calc;
	ASSERT_EQUAL(calc.Pow(2, 5), 32);
	ASSERT_EQUAL(calc.Pow(8, 0), 1);
	ASSERT_EQUAL(calc.Pow(0, 0), 1);
	ASSERT_EQUAL(calc.Pow(0, 11), 0);
	ASSERT_EQUAL(calc.Pow(-5, 3), -125);
	ASSERT_EQUAL(calc.Pow(-11, 2), 121);
	ASSERT_EQUAL(calc.Pow(5, 1), 5);
	ASSERT_EQUAL(calc.Pow(9, -2), 0);
	ASSERT_EQUAL(calc.Pow(1, 345), 1);

	if (fails_count == 0)
	{
		std::cerr << "TestPow: OK" << std::endl;
	}
	else
	{
		std::cerr << "TestPow, fails_count = " << fails_count << std::endl;
	}
	std::cerr << "------------------" << std::endl;

}

void TestGCD()
{
	std::cerr << "------------------";
	int fails_count = 0;
	Calculator calc;
	ASSERT_EQUAL(calc.GCD(5, 1), 1);
	ASSERT_EQUAL(calc.GCD(1, 5), 1);
	ASSERT_EQUAL(calc.GCD(0, 56), 56);
	ASSERT_EQUAL(calc.GCD(-75, 25), 25);
	ASSERT_EQUAL(calc.GCD(77, -11), 11);
	ASSERT_EQUAL(calc.GCD(-154, -616), 154);
	ASSERT_EQUAL(calc.GCD(7, 3), 1);
	ASSERT_EQUAL(calc.GCD(60, 42), 6);
	
	if (fails_count == 0)
	{
		std::cerr << "TestGCD: OK" << std::endl;
	}
	else
	{
		std::cerr << "TestGCD, fails_count = " << fails_count << std::endl;
	}
	std::cerr << "------------------" << std::endl;

}


void TestLCM()
{
	std::cerr << "------------------";
	int fails_count = 0; 
	Calculator calc;
	ASSERT_EQUAL(calc.LCM(2, 3), 6);
	ASSERT_EQUAL(calc.LCM(15, 1), 15);
	ASSERT_EQUAL(calc.LCM(-75, 25), 75);
	ASSERT_EQUAL(calc.LCM(512, -8), 512);
	ASSERT_EQUAL(calc.LCM(0, 9), 0);
	ASSERT_EQUAL(calc.LCM(43, 47), 2021);
	ASSERT_EQUAL(calc.LCM(43, 47), 2021);
	ASSERT_EQUAL(calc.LCM(3517, 331), 1164127);
	
	if (fails_count == 0)
	{
		std::cerr << "TestLCM: OK" << std::endl;
	}
	else
	{
		std::cerr << "TestLCM, fails_count = " << fails_count << std::endl;
	}
	std::cerr << "------------------" << std::endl;

}


void TestCheckSignEqual()
{
	std::cerr << "------------------";
	int fails_count = 0;
	Calculator calc;
	ASSERT_EQUAL(calc.CheckSignEqual(2, 3), 1);
	ASSERT_EQUAL(calc.CheckSignEqual(3, 2), 1);
	ASSERT_EQUAL(calc.CheckSignEqual(-1, 5), 0);
	ASSERT_EQUAL(calc.CheckSignEqual(4, -3), 0);
	ASSERT_EQUAL(calc.CheckSignEqual(-5, -6), 1);
	ASSERT_EQUAL(calc.CheckSignEqual(0, -5), 1);
	ASSERT_EQUAL(calc.CheckSignEqual(7, 0), 1);
	ASSERT_EQUAL(calc.CheckSignEqual(0, 0), 1);

	if (fails_count == 0)
	{
		std::cerr << "TestCheckSignEqual: OK" << std::endl;
	}
	else
	{
		std::cerr << "TestCheckSignEqual, fails_count = " << fails_count << std::endl;
	}
	std::cerr << "------------------" << std::endl;

}