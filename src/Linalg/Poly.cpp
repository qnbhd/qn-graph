//
// Created by qnbhd on 11.12.2019.
//

#include "Poly.hpp"

Poly::Poly() {
    deg_ = 0;
    coefficients_ = {0};
}

Poly::Poly(std::vector<double> coefficients) {
    coefficients_ = std::move(coefficients);
    deg_ = coefficients_.size() - 1;
}

Poly::Poly(const Poly & poly) {
    coefficients_ = poly.coefficients_;
    deg_ = poly.deg_;
}

Poly &Poly::operator=(const Poly &right) {
    if (this == &right) {
        return *this;
    }

    coefficients_ = right.coefficients_;
    deg_ = right.deg_;

    return *this;
}

double Poly::Calculate(double x0) {
    double result = 0;

    for (size_t i = 0; i < deg_+1; ++i)
        result += coefficients_[i] * pow(x0, i);

    return result;
}

void Poly::SetCoefficient(std::vector<double> coefficients) {
    coefficients_ = std::move(coefficients);
    deg_ = coefficients_.size() - 1;
}

std::ostream &operator<<(std::ostream &out, Poly poly) {
    size_t pos = 0;

    for (auto a : poly.coefficients_) {
        if (pos++ == 0)
        {
            out << a;
        }
        else
        {
            if (a >= 0)
                out << '+';
            out << a << "*x^" << pos-1;
        }
    }

    out << std::endl;

    return out;
}
