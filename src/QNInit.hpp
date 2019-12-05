//
// Created by qnbhd on 05.12.2019.
//

#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define QnWindowSettings __APPLICATION_DEFAULT_TITLE ,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, \
                         __APPLICATION_SIZE_WIDTH , __APPLICATION_SIZE_HEIGHT,SDL_WINDOW_SHOWN

class QNInit {
private:

    SDL_Window*   QnWindow_;

    SDL_Renderer* QnRenderer_;

public:

    QNInit ();

    ~QNInit();

    bool SDLInit ();

    bool WindowInit ();

    bool RenderInit ();

    bool IMGInit ();

    bool TTFInit ();

    SDL_Window* GetWindow ();

    SDL_Renderer* GetRenderer();

};

