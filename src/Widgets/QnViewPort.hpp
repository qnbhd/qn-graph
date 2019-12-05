//
// Created by qnbhd on 05.12.2019.
//

#pragma once

#include <SDL_rect.h>

struct QnViewPort
{
    SDL_Rect ViewPort_;

    explicit QnViewPort (SDL_Rect viewport) : ViewPort_(viewport)
    {}

    QnViewPort (int x, int y, int w, int h) : ViewPort_({x, y, w, h})
    {}

    //// Other features

};
