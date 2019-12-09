//
// Created by qnbhd on 25.11.2019.
//

#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "Token.h"
#include "TokenType.h"


class Lexer  {
public:

    Lexer () : input_(std::string("")), pos_(0),
               length_(0), tokens_(std::vector<Token>())
    {}

    explicit Lexer (std::string input) : input_(std::move(input)), pos_(0)
    {
        length_ = input_.size();
        tokens_ = std::vector<Token>();
    }

    void setInput (std::string input)
    {
        input_ = std::move(input);
        pos_ = 0;
        length_ = input_.size();
        tokens_ = std::vector<Token>();
        /////
    }

    std::vector<Token> tokenize ();

private:

    std::string input_;

    std::vector<Token> tokens_;

    size_t pos_;

    size_t length_;

    void tokenizeNumber ();

    void tokenizeOperator ();

    void tokenizeWord ();

    void addToken (TokenType type);

    void addToken (TokenType type, const std::string& text);

    char peek (int relPos);

    char next ();

    /////

    std::string OPERATORS_CHARS = "+-*/()^";
    std::vector<TokenType> OPERATOR_TOKENS = {
            TokenType::PLUS, TokenType::MINUS,
            TokenType::STAR, TokenType::SLASH,
            TokenType::LPAREN, TokenType::NPAREN,
            TokenType::POW
    };

    bool close_ = false;

};


