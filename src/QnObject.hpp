//
// Created by qnbhd on 05.12.2019.
//

#pragma once

#include <SDL_rect.h>
#include <SDL.h>

class QnObject
{
public:

    QnObject() = default;

    virtual ~QnObject() = default;

    virtual void Hide () = 0;

    virtual void Redraw () = 0;

    virtual void SetPos (SDL_Point) = 0;

    virtual SDL_Point GetPos () = 0;

    virtual void HandleEvent (SDL_Event) = 0;

};

