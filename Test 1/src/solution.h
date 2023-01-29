#pragma once

#include <stdexcept>

inline bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

inline bool isOperation(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

inline double toDouble(char c)
{
    if(c < '0' || c > '9')
        throw std::invalid_argument("Non-digit passed to toDouble()");
        
    return c - '0';
}

double perform(char operation, double left, double right);
double evaluateRpn(const char* rpn);