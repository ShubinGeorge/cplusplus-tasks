#include <iostream>
#include <cmath>
#include "calculator.h"


int Calculator::Sum(const int lhs, const int rhs)
{
    return lhs + rhs;
}


int Calculator::Def(const int lhs, const int rhs)
{ 
    return lhs - rhs;
}


int Calculator::Division(const int divinded, const int divider)
{
    if (divider == 0)
    {
        return 0;
    }
    return (int) (divinded / divider);
}


int Calculator::Multiplicattion(const int rhs, const int lhs)
{
    return rhs * lhs;
}

int Calculator::Pow(const int base, const int degree)
{
    if (degree < 0)
    {
        return 0;
    }
    if (degree == 0)
    {
        return 1;
    }
    else if (base == 1)
    {
        return base;
    }
    else if (degree % 2 == 0)
    {
        return pow(base * base, degree / 2);
    }
    else
    {
        return pow(base * base, degree / 2) * base;
    }  
}


int Calculator::GCD(const int lhs, const int rhs)
{
    int lhs_copy = abs(lhs);
    int rhs_copy = abs(rhs);
    while (rhs_copy != 0)
    {
        int tmp = rhs_copy;
        rhs_copy = lhs_copy % rhs_copy;
        lhs_copy = tmp;
    }
    return lhs_copy;
}


int Calculator::LCM(const int lhs, const int rhs)
{
    int result = 0;
	int lhs_copy = abs(lhs);
	int rhs_copy = abs(rhs);
    result = rhs_copy * lhs_copy / GCD(lhs_copy, rhs_copy);
    return result;
}


bool Calculator::CheckSignEqual(const int lhs, const int rhs)
{
    if (lhs == 0 || rhs == 0)
    {
        return 1;
    }
    return (lhs * rhs) > 0;
}