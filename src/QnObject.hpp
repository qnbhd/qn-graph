//
// Created by qnbhd on 05.12.2019.
//

#pragma once

#include <SDL_rect.h>

class QnObject
{
public:

    QnObject() = default;

    virtual ~QnObject() = default;

    virtual void Hide () = 0;

    virtual void Redraw () = 0;

    virtual void SetPos (SDL_Point) = 0;

};

