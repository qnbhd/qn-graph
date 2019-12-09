//
// Created by qnbhd on 25.11.2019.
//

#pragma once
#include <utility>
#include <vector>
#include "Token.h"
#include "TokenType.h"
#include "Expression.hpp"
#include "CVExpression.hpp"
#include "UnaryExpression.h"
#include "FuncExpression.hpp"

/// метод рекурсивного спуска

class Parser {
private:

    Expression* EXPRESSION ();
    Expression* ADD ();
    Expression* MULTY ();
    Expression* POW();
    Expression* UNARY ();
    Expression* PRIMARY ();

    std::vector<Token> tokens_;

    size_t size_;

    size_t pos_;

    Token get (int);

    Token EOFF = Token(TokenType::EOFF, "");

    bool match (TokenType);

public:

    Parser () : tokens_(std::vector<Token>()), size_(0), pos_(0)
    {}

    explicit Parser (std::vector<Token> tokens) :
        tokens_(std::move(tokens)), size_(tokens_.size()), pos_(0) // tokens обнуляется
    {}

    ~Parser ();

    void setTokens (std::vector<Token> tokens)
    {
        tokens_ = std::move(tokens);
        size_ = tokens_.size();
        pos_ = 0;
    }

    std::vector<Expression*> parse ();


};

