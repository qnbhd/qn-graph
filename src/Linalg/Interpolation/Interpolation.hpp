//
// Created by qnbhd on 03.12.2019.
//

#pragma once

#include <vector>

#include <iostream>
#include "../Matrix/Matrix.hpp"
#include "../SLE/SLE.hpp"
#include "../Poly.hpp"
#include <cmath>



class Interpolation {
public:
    static void Lagranj (std::vector<double> X, std::vector<double> y, std::vector<double>& answer, Poly& poly)
    {
        auto MainSize = X.size();

        if (MainSize != y.size())
            throw std::invalid_argument("[ERROR] length of X and y are different");

        Matrix<double> SL (MainSize, MainSize + 1);

        for (size_t j = 0; j < MainSize; ++j)
            for (size_t i = 0; i < MainSize; ++i)
                SL.at(i, j) = pow ( X.at(i), j );

        for (size_t i = 0; i < MainSize; ++i)
            SL.at(i, MainSize) = y.at(i);

        answer.reserve(MainSize);

        SLE::gauss(SL, answer);

        poly.SetCoefficient(answer);

    }

};

