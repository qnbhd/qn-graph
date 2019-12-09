//
// Created by qnbhd on 25.11.2019.
//

#pragma once

class Expression {
public:

    virtual ~Expression() = default;

    virtual double eval () = 0;

    virtual std::string to_string () = 0;

    
};

