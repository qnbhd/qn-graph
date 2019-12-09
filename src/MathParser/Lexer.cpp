//
// Created by qnbhd on 25.11.2019.
//

#include "Lexer.h"
#include "FunctionTable.hpp"


void
Lexer::addToken (TokenType type)
{
    addToken (type, "");
}

void
Lexer::addToken (TokenType type, const std::string& text)
{
    tokens_.emplace_back(type, text);
}

char
Lexer::peek (int relPos)
{
    auto position = pos_ + relPos;
    if (position >= length_)
        return '\0';
    return input_.at(position);
}

char
Lexer::next ()
{
    pos_++;
    return peek(0);
}

std::vector<Token> Lexer::tokenize()
{
    while (pos_ < length_)
    {
        char current = peek(0);
        //std::cout << current << " ";
        if (isdigit(current))
        {
            tokenizeNumber();

            /*if (close_) {
                addToken(TokenType::NPAREN);
                close_ = false;
            }*/
        }
        else if ( (current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z'))
        {
            tokenizeWord();

            /*if (close_) {
                addToken(TokenType::NPAREN);
                close_ = false;
            }*/
        }
        else if (OPERATORS_CHARS.find(current) != std::string::npos)
        {
            tokenizeOperator();
        }
        else
        {
            next();
        }


    }

    return tokens_;
}

void Lexer::tokenizeNumber()
{
    std::stringstream stringBuffer;
    char current = peek(0);

    while (isdigit(current))
    {
        stringBuffer << current;
        current = next();

        if (current == '.' && stringBuffer.str().find('.') == std::string::npos)
        {
            stringBuffer << current;
            current = next();
        } else if (current == '.' && stringBuffer.str().find('.') != std::string::npos)
        {
            throw std::runtime_error("[ERROR] INVALID REAL NUMBER");
        }
    }

    addToken(TokenType::NUMBER, stringBuffer.str() );
}

void
Lexer::tokenizeWord()
{
    std::stringstream stringBuffer;
    char current = peek(0);

    while (true)
    {
        if (!isdigit(current) && !(current >= 'a' && current <= 'z') &&
            !(current >= 'A' && current <= 'Z')  && current != '_')
        {
            break;
        }

        stringBuffer << current;
        current = next();
    }

    if (FunctionTable::isExist(stringBuffer.str()))
    {
        addToken(TokenType::FUNC, stringBuffer.str());
    } else {
        addToken(TokenType::WORD, stringBuffer.str() );
    }
}


void Lexer::tokenizeOperator()
{
    size_t position = OPERATORS_CHARS.find(peek(0));
    addToken(OPERATOR_TOKENS[position]);

    /*if (OPERATORS_CHARS[position] == '^')
    {
        tokens_.insert((tokens_.end() - 2), Token(TokenType::LPAREN, ""));
        close_ = true;
    }*/

    next();
}