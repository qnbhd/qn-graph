//
// Created by qnbhd on 25.11.2019.
//

#include "Parser.hpp"
#include "NumberExpression.hpp"
#include "BinaryExpression.hpp"

std::vector<Expression*>
Parser::parse()
{
    std::vector<Expression*> result;
    while (!match(TokenType::EOFF)){
        result.push_back(EXPRESSION());
    }
    return result;
}

Token
Parser::get(int relPos)
{
    size_t position = pos_ + relPos;
    if (position >= size_) return EOFF;
    return tokens_.at(position);
}

bool
Parser::match(TokenType type) {
    auto current = get(0);
    if (current.getType() != type)
        return false;
    pos_++;
    return true;
}

Expression*
Parser::EXPRESSION() {
    return ADD();
}

Expression*
Parser::ADD()
{
    Expression * result = MULTY();

    while (true)
    {
        if (match(TokenType::PLUS))
        {
            result = new BinaryExpression('+', result, MULTY());
            continue;
        }
        if (match(TokenType::MINUS))
        {
            result = new BinaryExpression('-', result, MULTY());
            continue;
        }
        break;
    }

    return result;
}

Expression *Parser::MULTY()
{
    Expression * result = UNARY();
    while (true)
    {
        if (match(TokenType::STAR))
        {
            result = new BinaryExpression('*', result, UNARY());
            continue;
        }

        if (match(TokenType::SLASH))
        {
            result = new BinaryExpression('/', result, UNARY());
            continue;
        }
        break;
    }

    return result;
}



Expression *Parser::UNARY()
{
    if (match(TokenType::MINUS))
    {
        return new UnaryExpression('-', POW());
    }

    return POW();
}

Expression *Parser::POW()
{
    Expression * result = PRIMARY();

    if (match(TokenType::POW))
    {
        return new BinaryExpression('^', result, PRIMARY());
    }

    return result;
}

Expression *Parser::PRIMARY()
{
    Token current = get(0);

    if (match(TokenType::NUMBER))
    {
        return new NumberExpression(std::stod(current.getText()));
    }

    if (match(TokenType::WORD))
    {
        return new CVExpression(current.getText());
    }

    if (match(TokenType::FUNC))
    {
        if (match(TokenType::LPAREN))
        {
            Expression * res = EXPRESSION();
            if (match(TokenType::NPAREN))
            {
                return new FuncExpression(current.getText(), res);
            } else
            {
                throw std::runtime_error("[ERROR] EXPECTED ')'");
            }
        } else
        {
            throw std::runtime_error("[ERROR] EXPECTED '('");
        }
    }

    if (match(TokenType::LPAREN))
    {
        Expression* result = EXPRESSION();
        if (!match(TokenType::NPAREN))
            throw std::runtime_error("[ERROR] EXPECTED ')'");
        return result;
    }


    throw std::runtime_error("[ERROR] UNKNOWN EXPRESSION");
}

Parser::~Parser() {
    // TODO
}
