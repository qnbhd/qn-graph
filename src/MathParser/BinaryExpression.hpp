//
// Created by qnbhd on 25.11.2019.
//

#pragma once
#include "Expression.hpp"
#include <iostream>

class BinaryExpression final : public Expression{
private:

    Expression* expr1_;

    Expression* expr2_;

    char operation_;

public:

    BinaryExpression (char operation, Expression* expr1, Expression* expr2):
        operation_(operation), expr1_(expr1), expr2_(expr2)
    {}

    ~BinaryExpression() override
    {
        delete expr1_;
        delete expr2_;
    }

    std::string to_string () override {
        return expr1_->to_string() + std::string(reinterpret_cast<const char *>(operation_)) + expr2_->to_string();
    }

    double eval () override
    {
        double left  = expr1_->eval();
        double right = expr2_->eval();

        switch (operation_)
        {
            case '-': return left - right;
            case '*': return left * right;
            case '^': return pow(left, right);
            case '/': {
                    double result;
                    if (right == 0.0)
                    {
                        throw std::invalid_argument("[ERROR] DIVISION BY ZERO");
                    }
                    return left / right;
            }
            case '+':
            default:
                return left + right;
        }
    }



};

