//
// Created by qnbhd on 28.11.2019.
//

#pragma once

#include "Expression.hpp"
#include "FunctionTable.hpp"
#include <string>
#include <utility>
#include <cmath>

enum FunctionNames
{
    SIN,
    COS,
    TG,
    TAN,
    CTG,
    COT,
    EXP,
    LN,
    LOG,
    SGN,
    SIGN,
    ABS,
    SQRT,
    CBRT,
    ASIN,
    ACOS,
    ATAN,
    ARCTG,
    ACOT,
    ARCCTG,
    SINH,
    COSH,
    TANH,
    COTH
};

class FuncExpression final : public Expression{
private:

    std::string function_;

    Expression* expr_;

public:

    FuncExpression(std::string func, Expression* expr) : function_(std::move(func)), expr_(expr)
    {}

    ~FuncExpression() override
    {
        delete expr_;
    }

    double eval () override
    {
        int idf = FunctionTable::get(function_);
        double result = expr_->eval();

        switch (idf)
        {
            case SIN:   return sin(result);
            case COS:   return cos(result);
            case TAN:   //down
            case TG:    return tan(result);
            case CTG:   //down
            case COT:   return 1/tan(result);
            case EXP:   return exp(result);
            case LN:    //down
            case LOG:   return log(result);
            case SGN:   //down
            case SIGN:  {
                            if (result < 0)
                                return -1;
                            else return result > 0 ? 1 : 0;
                        }
            case ABS:   return std::abs(result);
            case SQRT:  return sqrt(result);
            case CBRT:  return cbrt(result);
            case ASIN:  return asin(result);
            case ACOS:  return acos(result);
            case ATAN:  //down
            case ARCTG: return atan(result);
            case ARCCTG: // down
            case ACOT:  return atan(1/result); // TODO EXCEPTION
            case SINH:  return sinh(result);
            case COSH:  return cosh(result);
            case TANH:  return tanh(result);
            case COTH:  return 1/tanh(result);
            default:
                return result;
        }
    }

    std::string to_string () override
    {
        return function_ + std::string("(") + std::to_string(expr_->eval()) + std::string(")");
    }
};
