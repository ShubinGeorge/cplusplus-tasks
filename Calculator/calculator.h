#pragma once




class Calculator 
{
public:
    int Sum(const int lhs, const int rhs);
    int Def(const int lhs, const int rhs);
    int Division(const int divinded, const int divider);
    int GCD(const int lhs, const int rhs);
    int LCM(const int lhs, const int rhs);
    int Pow(const int lhs, const int rhs);
    int Multiplicattion(const int rhs, const int lhs);    
    bool CheckSignEqual(const int lhs, const int rhs);
};