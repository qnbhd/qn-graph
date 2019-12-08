//
// Created by qnbhd on 05.12.2019.
//

#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "QNSETTINGS.hpp"
#include "QNInit.hpp"

#include "QNDekart.hpp"
#include "QnObject.hpp"
#include "QnPlotter.hpp"
#include "QnTexture.hpp"
#include "Widgets/QnButton.hpp"
#include "Widgets/QnViewPort.hpp"

#define MAXEPS 60
#define MINEPS 25

enum QnScrollState
{
    NONE,
    MOUSE_DOWN,
    MOUSE_DOWN_AND_MOVE,
    MOUSE_UP
};

#include <vector>

class QNApplication {

private:

    SDL_Window * QnMainWindow;

    SDL_Renderer * QnMainRenderer;

    int ScrollState = QnScrollState::NONE;

    QNInit QNi;

    bool QnQuit;

    static double f(double x)
    {
        return sin(x);
    }

public:

    QNApplication();

    void QNMainLoop();

    ~QNApplication();

    void QNMainEventHandler(SDL_Event);

    void QNScrollEventHandler (SDL_Event, QnViewPort, QNDekart&, int&, int&);


};

