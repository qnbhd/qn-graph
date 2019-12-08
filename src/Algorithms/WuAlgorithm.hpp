//
// Created by qnbhd on 08.12.2019.
//

#include <cmath>
#include <algorithm>
#include <SDL_system.h>

#pragma once

class WuAlgorithm
{
private:
    static double round(double x) { return floor(x + 0.5); }
    static double fPart(double x) { return x - floor(x); }
    static double rfPart(double x) { return 1 - fPart(x); }

    static void plot (SDL_Renderer* renderer, double x, double y, SDL_Color color, double brightness)
    {
        /////// NOT USE BRIGHTNESS BY COLOR /////
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, brightness);
        SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
    }

public:
    static void Line(SDL_Renderer * renderer, double x0, double y0, double x1, double y1, SDL_Color color)
    {
        bool steep = fabs(y1 - y0) > fabs(x1 - x0);

        if (steep)
        {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }

        if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        double dx = x1 - x0;
        double dy = y1 - y0;

        double gradient = dx == 0.0  ? 1.0 : dy / dx;

        double xEnd = round(x0);
        double yEnd = y0 + gradient * (xEnd - x0);
        double xGap = rfPart(x0 + 0.5);
        double xPixel1 = xEnd;
        double yPixel1 = floor(yEnd);

        if (steep)
        {
            plot(renderer, yPixel1,     xPixel1, color, rfPart(yEnd) * xGap);
            plot(renderer, yPixel1 + 1, xPixel1, color, fPart(yEnd) * xGap);
        }

        else
        {
            plot(renderer, xPixel1, yPixel1,        color,rfPart(yEnd) * xGap);
            plot(renderer, xPixel1, yPixel1 + 1, color, fPart(yEnd) * xGap);
        }

        double yIntersection = yEnd + gradient;

        xEnd = round(x1);
        yEnd = y1 + gradient * (xEnd - x1);
        xGap = fPart(x1 + 0.5);
        double xPixel2 = xEnd;
        double yPixel2 = floor(yEnd);

        if (steep)
        {
            plot(renderer, yPixel2,     xPixel2, color, rfPart(yEnd) * xGap);
            plot(renderer, yPixel2 + 1, xPixel2, color,fPart(yEnd) * xGap);

            for (int x = static_cast<int>(xPixel1) + 1; x <= (xPixel2 - 1); x++)
            {
                plot(renderer, yIntersection    , x, color, rfPart(yIntersection));
                plot(renderer, yIntersection + 1, x, color,  fPart(yIntersection));
                yIntersection += gradient;
            }
        }

        else
        {
            plot(renderer, xPixel2, yPixel2,        color, rfPart(yEnd) * xGap);
            plot(renderer, xPixel2, yPixel2 + 1, color, fPart(yEnd) * xGap);

            for (int x = static_cast<int>(xPixel1) + 1; x <= (xPixel2 - 1); x++)
            {
                plot(renderer, x, yIntersection,        color, rfPart(yIntersection));
                plot(renderer, x, yIntersection + 1, color,  fPart(yIntersection));
                yIntersection += gradient;
            }
        }
    }


};
