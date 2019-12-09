//
// Created by qnbhd on 25.11.2019.
//

#pragma once
#include "Expression.hpp"

class NumberExpression final : public Expression {
public:

    explicit NumberExpression(double value) : value_(value)
    {}

    ~NumberExpression() override = default;

    double eval () override
    {
        return value_;
    }

    std::string to_string () override
    {
        return std::to_string(value_);
    }

private:

    double value_;
};

