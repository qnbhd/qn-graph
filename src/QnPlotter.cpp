//
// Created by qnbhd on 08.12.2019.
//

#include <iostream>
#include "QnPlotter.hpp"

void QnPlotter::Point(SDL_Renderer * renderer, int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
    SDL_RenderDrawPoint(renderer, x, y);
}

void QnPlotter::Line(SDL_Renderer * renderer, SDL_Point from, SDL_Point to, SDL_Color color) {
    WuAlgorithm::Line(renderer, from.x, from.y, to.x, to.y, color);
}

void QnPlotter::Points(SDL_Renderer * renderer, const VectorPoints& points, SDL_Color color) {
    for (auto [x, y] : points)
        Point(renderer, x, y, color);
}

void QnPlotter::Curve(SDL_Renderer * renderer, const VectorPoints &points, SDL_Color color) {
    for (int i = 1; i < points.size(); ++i)
    {
        auto [x1, y1] = points[i-1];
        auto [x2, y2] = points[i];

        Line(renderer, {x1,y1}, {x2,y2}, color);
    }
}

void QnPlotter::Curve(SDL_Renderer * renderer, QNDekart& QnSC, double start, double end, f function, SDL_Color color) {
    for (; start < end; )
    {
        auto x2 = start + __PLOT_DX;
        auto y1 = function(start);
        auto y2 = function(x2);

        if (isinf(y1))
            continue;
        if (isinf(y2))
            continue;

        auto from = QnSC.DekartToScreen(start, y1);
        auto to   = QnSC.DekartToScreen(x2, y2);

        //std::cout << start << " " << y1 << " " << x2 << " " << y2 << std::endl;
        //Line(renderer, from, to, color);

        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderDrawLine(renderer, from.x, from.y, to.x, to.y);

        start += __PLOT_DX;
    }
}

void QnPlotter::Curve(SDL_Renderer *renderer, MathParser &mp, QNDekart &QnSC, double start, double end,
                      SDL_Color color) {
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );

    for (; start < end; ) {
        auto x2 = start + __PLOT_DX;
        auto y1 = mp.Calculate(start);
        auto y2 = mp.Calculate(x2);

        //std::cout << abs(y1 - y2) << std::endl;

        if (isinf(y1))
            continue;
        if (isinf(y2))
            continue;

        auto from = QnSC.DekartToScreen(start, y1);
        auto to   = QnSC.DekartToScreen(x2, y2);


        SDL_RenderDrawLine(renderer, from.x, from.y, to.x, to.y);

        start += __PLOT_DX;
    }

}






