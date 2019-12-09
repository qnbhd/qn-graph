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

class Approximation
{
public:
    static void MNK (const std::vector<double>& X, const std::vector<double>& Y,
                     double deg, std::vector<double>& answer, Poly& poly)
    {
        deg+=1;

        Matrix<double> matrix (deg, deg+1);

        for (int i = 0; i < deg; ++i)
            matrix.at(i,0) = degSum(X, i);

        for (int j = 1; j < deg; ++j)
            matrix.at(deg-1,j) = degSum(X, deg+j-1);

        for (int j = 1; j < deg; ++j)
            for (int i = 0; i < deg - 1; ++i)
                matrix.at(i,j) = matrix.at(i+1, j-1);

        for (int i = 0; i < deg; ++i)
            matrix.at(i, deg) = degSum(X, Y, i);

        answer.reserve(deg+1);

        SLE::gauss(matrix, answer);

        poly.SetCoefficient(answer);

    }

    static double degSum (const std::vector<double>& xx, double deg)
    {
        double result = 0.0;

        for (auto xz : xx)
            result += pow(xz, deg);

        return result;
    }

    static double degSum (std::vector<double> xx, std::vector<double> yy, double deg) // for sum (x_i)^j * y_i
    {
        double result = 0.0;

        for (int i = 0; i < xx.size(); ++i)
            result += yy[i] * pow(xx[i], deg);

        return result;
    }




};