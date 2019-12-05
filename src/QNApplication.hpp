//
// Created by qnbhd on 05.12.2019.
//

#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "QNSETTINGS.hpp"
#include "QNInit.hpp"

#include "QnObject.hpp"
#include "QnTexture.hpp"
#include "Widgets/QnButton.hpp"
#include "Widgets/QnViewPort.hpp"
#include <vector>

class QNApplication {

private:

    SDL_Window * QnMainWindow;

    SDL_Renderer * QnMainRenderer;

    QNInit QNi;

    bool QnQuit;

public:

    QNApplication();

    void QNMainLoop();

    ~QNApplication();

    void QNMainEventHandler(SDL_Event);

};

