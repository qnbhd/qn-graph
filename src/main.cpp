#include <iostream>

#include "QNApplication.hpp"

std::map<std::string, double> CVTable::consts_  = {
        std::make_pair("pi",  3.14),
        std::make_pair("e" ,  2.71),
        std::make_pair("phi", 1.61)
};

std::map<std::string, double>  CVTable::variables_ = {
        std::make_pair("x", 0.0) // make new variables for any expressions!
};

std::map<std::string, int> FunctionTable::functions_ = {
        std::make_pair("sin",  SIN),
        std::make_pair("cos",  COS),
        std::make_pair("tg",   TG),
        std::make_pair("tan",  TAN),
        std::make_pair("ctg",  CTG),
        std::make_pair("cot",  COT),
        std::make_pair("exp",  EXP),
        std::make_pair("ln",   LN),
        std::make_pair("sgn",  SGN),
        std::make_pair("sign", SIGN),
        std::make_pair("abs",  ABS),
        std::make_pair("sqrt", SQRT),
        std::make_pair("cbrt", CBRT),
        std::make_pair("asin", ASIN),
        std::make_pair("acos", ACOS),
        std::make_pair("atan", ATAN),
        std::make_pair("arctg", ARCTG),
        std::make_pair("acot", ACOT),
        std::make_pair("sinh", SINH),
        std::make_pair("cosh", COSH),
        std::make_pair("tanh", TANH),
        std::make_pair("coth", COTH)

};

int main( int argc, char* args[] )
{
    QNApplication Qapp;

    return 0;
}