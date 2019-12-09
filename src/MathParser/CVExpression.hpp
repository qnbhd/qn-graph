
//
// Created by qnbhd on 28.11.2019.
//

#pragma once
#include "Expression.hpp"
#include <iostream>
#include <string>
#include <utility>
#include "CVTable.hpp"

class CVExpression final : public Expression
{
private:

    std::string name_;

public:

    explicit CVExpression(std::string name) : name_(std::move(name))
    {}

    ~CVExpression() override = default;

    double eval () override
    {

        if (CVTable::ConstIsExists(name_))
            return CVTable::getConst(name_);

        if (CVTable::VarIsExists(name_))
            return CVTable::getVariable(name_);

        throw std::runtime_error("[ERROR] CONST OR VARIABLE DOESN'T EXIST");
    }

    std::string to_string () override
    {
        return name_;
    }
};