//
// Created by qnbhd on 25.11.2019.
//

#pragma once

#include "TokenType.h"
#include <iostream>
#include <string>
#include <utility>

class Token final {
private:

    TokenType type_;

    std::string text_;
public:

    Token() = default;

    Token (TokenType type, std::string text) : type_(type), text_(std::move(text))
    {}

    [[nodiscard]] TokenType getType () const
    {
        return type_;
    }

    void setType (TokenType type)
    {
        type_ = type;
    }

    [[nodiscard]] std::string getText () const
    {
        return text_;
    }

    void setText (std::string text)
    {
        text_ = std::move(text);
    }

};




