//
// Created by qnbhd on 06.12.2019.
//

#pragma once

#include <SDL_system.h>
#include "QnObject.hpp"
#include "QNSETTINGS.hpp"
#include <cmath>
#include <vector>

#define _NET_OFFSET_X 10
#define _NET_OFFSET_Y 10
#define _START_EPS    40
#define CALCULATE_DXY(I) -0.25714 * (I) + 16.429

#define XDKS(X) QnAxisPos_.x + (X)/abs(-0.25714*(eps_) + 16.429) * eps_
#define YDKS(Y) QnAxisPos_.y - (Y)/abs(-0.25714*(eps_) + 16.429) * eps_


typedef std::vector<std::pair<int,int>> VectorPoints;


struct QnInterval
{
    int leftBound;
    int rightBound;
};

class QNDekart : public QnObject {
private:

    SDL_Renderer * QnRenderer_;

    SDL_Point QnAxisPos_;

    int eps_ = _START_EPS;

    QnInterval interval_;

    void DrawAxis (SDL_Point, SDL_Color = __SETTINGS_BLACK_COLOR);

    void DrawNet (SDL_Color);


public:

    QNDekart (SDL_Renderer * rd, SDL_Point pt) : QnRenderer_(rd), QnAxisPos_(pt)
    {
        DrawAxis(pt);
    }

    ~QNDekart() override;

    void Hide () override;

    void Redraw () override;

    void SetPos (SDL_Point) override;

    void SetEps (int);

    QnInterval GetInterval ();

    void HandleEvent (SDL_Event e) override
    {}

    int GetEps();

    SDL_Point GetPos ();

    static void DrawLine (SDL_Renderer *, SDL_Point from, SDL_Point to, int brushWidth, SDL_Color);

    SDL_Point DekartToScreen (double x, double y);

};


