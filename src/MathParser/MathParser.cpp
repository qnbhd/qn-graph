//
// Created by qnbhd on 29.11.2019.
//

#include "MathParser.hpp"

#include <utility>

MathParser::MathParser() {
    EXPRESSION_ = std::string("");
}

bool MathParser::ExpressionIsEmpty() const {
    return EXPRESSION_ == std::string("");
}

MathParser::MathParser(std::string expression) {
    EXPRESSION_= std::move(expression);
    LEXER_.setInput(EXPRESSION_);
    PARSER_.setTokens(LEXER_.tokenize());
    EXRESULT_ = PARSER_.parse();
}

MathParser::~MathParser() {
    for (auto expression : EXRESULT_)
        delete expression;
}

void MathParser::SetExpression(std::string expression) {
    if (expression.length() == 1)
        throw std::runtime_error("Invalid expression");

    auto posy = expression.find('y');
    auto pose =  expression.find('=');
    if (posy != std::string::npos && pose != std::string::npos)
    {
        expression = expression.substr(pose);
    }

    EXPRESSION_ = std::move(expression);
    LEXER_.setInput(EXPRESSION_);

    /*for (auto c : LEXER_.tokenize())
        std::cout << c.getText() << ":" << c.getType() << std::endl;
    */

    PARSER_.setTokens(LEXER_.tokenize());
    EXRESULT_ = PARSER_.parse();
}

std::vector<double> MathParser::Calculate(const std::vector<double>& range) {
    std::vector<double> Y;
    Y.reserve(range.size());
    for (auto exp : range)
        Y.push_back(Calculate(exp));
    return Y;
}

double MathParser::Calculate(double x) {
    if(!ExpressionIsEmpty() && EXRESULT_.size() > 0)
    {
        CVTable::setVariable("x", x);
        return EXRESULT_.at(0)->eval();
    }

    throw std::runtime_error("[ERROR] EXPRESSION IS EMPTY");
}

std::vector<double> MathParser::MakeLinspace(double from, double to, double hop)
{
    std::vector<double> linspace;

    for (; from <= to; )
        linspace.push_back(from), from += hop;

    return linspace;
}

std::vector<double> MathParser::Calculate(double from, double to, double hop) {
    return Calculate(MakeLinspace(from, to, hop));
}

