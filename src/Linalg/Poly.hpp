//
// Created by qnbhd on 03.12.2019.
//

#pragma once
#include <utility>
#include <vector>
#include <cmath>
#include <ostream>

class Poly
{
private:
    std::vector<double> coefficients_;
    size_t deg_;
public:

    Poly();

    explicit Poly(std::vector<double> coefficients);

    virtual ~Poly() = default;

    Poly (const Poly&);

    Poly& operator=(const Poly& right);

    void SetCoefficient (std::vector<double> coefficients);

    double Calculate (double x0);

    friend std::ostream& operator<<(std::ostream& out, Poly poly) ;

};

