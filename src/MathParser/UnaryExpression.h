//
// Created by qnbhd on 28.11.2019.
//

#pragma once

#include "Expression.hpp"

class UnaryExpression final: public Expression
{
private:

    Expression* expr1_;

    char operation_;

public:

    UnaryExpression (char operation, Expression* expression): operation_(operation), expr1_(expression)
    {}

    ~UnaryExpression() override
    {
        delete expr1_;
    }

    double eval () override
    {
        switch (operation_)
        {
            case '-': return -expr1_->eval();
            default: return expr1_->eval();
        }
    }

    std::string to_string () override
    {
        return std::string(reinterpret_cast<const char *>(operation_)) + std::to_string(expr1_->eval());
    }
};