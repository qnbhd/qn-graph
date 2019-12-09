//
// Created by qnbhd on 02.12.2019.
//

#pragma once

#include "../Matrix/Matrix.hpp"
#include <vector>
#include <cmath>
#include <climits>

#define EPS 10e-5
class SLE {
public:
    static int gauss (Matrix<double> a, std::vector<double> & ans) {

        int n = static_cast<int>(a.rows());
        int m = static_cast<int>(a.columns() - 1);

        std::vector<int> where (m, -1);
        for (int col=0, row=0; col<m && row<n; ++col) {
            int sel = row;
            for (int i=row; i<n; ++i)
                if (std::abs (a.at(i, col)) > std::abs (a.at(sel, col)))
                    sel = i;
            if (std::abs (a[sel][col]) < EPS)
                continue;
            for (int i=col; i<=m; ++i)
                std::swap (a.at(sel,i), a.at(row,i));
            where[col] = row;

            for (int i=0; i<n; ++i)
                if (i != row) {
                    double c = a[i][col] / a[row][col];
                    for (int j=col; j<=m; ++j)
                        a[i][j] -= a[row][j] * c;
                }
            ++row;
        }

        ans.assign (m, 0);
        for (int i=0; i<m; ++i)
            if (where[i] != -1)
                ans[i] = a.at(where[i],m) / a.at(where[i],i);
        for (int i=0; i<n; ++i) {
            double sum = 0;
            for (int j=0; j<m; ++j)
                sum += ans[j] * a.at(i,j);
            if (std::abs(sum - a.at(i,m)) > EPS)
                return 0;
        }

        for (int i=0; i<m; ++i)
            if (where[i] == -1)
                return INT_MAX;
        return 1;
    }
};

