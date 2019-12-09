//
// Created by qnbhd on 29.11.2019.
//

#pragma once

#include "Lexer.h"
#include "Parser.hpp"
#include <vector>
#include "CVTable.hpp"
#include <cmath>

class MathParser  {
private:

    std::string EXPRESSION_;

    Lexer LEXER_;

    Parser PARSER_;

    std::vector<Expression*> EXRESULT_;

public:

    MathParser ();

    explicit MathParser (std::string);

    virtual ~MathParser ();

    [[nodiscard]] bool ExpressionIsEmpty () const;

    void SetExpression (std::string);

    std::vector<double> Calculate (const std::vector<double>&);

    double Calculate (double);

    static std::vector<double> MakeLinspace (double from, double to, double hop);

    std::vector<double> Calculate (double from, double to, double hop);

};
