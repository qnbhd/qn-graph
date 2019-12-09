//
// Created by qnbhd on 08.12.2019.
//

#pragma once


#include <SDL_system.h>
#include "Algorithms/WuAlgorithm.hpp"
#include "QNDekart.hpp"
#include <vector>
#include <utility>

#define __PLOT_DX 1e-1

using f = double(double);

class QnPlotter {
private:

public:

    static void Point (SDL_Renderer*, int, int, SDL_Color);

    static void Points (SDL_Renderer*, const VectorPoints& points, SDL_Color);

    static void Line (SDL_Renderer*, SDL_Point, SDL_Point, SDL_Color);

    static void Curve (SDL_Renderer*, const VectorPoints& points, SDL_Color);

    static void Curve(SDL_Renderer *renderer, QNDekart &QnSC, double start, double end, f function, SDL_Color color);

    static void Curve(SDL_Renderer *renderer, MathParser& mp, QNDekart &QnSC, double start, double end, SDL_Color color);
};

