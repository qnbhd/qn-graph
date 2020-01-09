//
// Created by qnbhd on 05.12.2019.
//

#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "QNSETTINGS.hpp"
#include "QNInit.hpp"
#include "QnFileDialog.hpp"

#include "QNDekart.hpp"
#include "QnObject.hpp"
#include "QnPlotter.hpp"
#include "QnTexture.hpp"
#include "Widgets/QnButton.hpp"
#include "Widgets/QnViewPort.hpp"
#include "Widgets/QnEdit.hpp"


#include "Linalg/Approximation/Approximation.hpp"
#include "Linalg/Poly.hpp"

#include <vector>
#include <sstream>

#define MAXEPS 60
#define MINEPS 25

struct CurveField
{
    QnEdit* editbox;
    QnButton* button;
    int points;

    friend bool operator==(const CurveField& left, const CurveField& right);
};


enum MathAction {
    APPROXIMATION_MNK,
    INTERPOLATION
};



enum QnScrollState
{
    NONE,
    MOUSE_DOWN,
    MOUSE_DOWN_AND_MOVE,
    MOUSE_UP
};



class QNApplication {

private:

    SDL_Window * QnMainWindow;

    SDL_Renderer * QnMainRenderer;

    int ScrollState = QnScrollState::NONE;

    QNInit QNi;

    bool QnQuit;

    std::vector<SDL_Color> CurvesColor_ = {
            {0xb9, 0x0, 0x05, 0x00},
            {0x6a, 0x0, 0x80, 0x00},
            {0x0, 0x3d, 0x33, 0xff},
            {0x54, 0x4c, 0x00,0xff},
            {0xd8, 0x43, 0x15,0xff},
            {0x01, 0x57, 0x9b,0xff}
    };

    std::vector<CurveField> curveFields;

    std::vector<std::pair<double, double>> appPoints;

    bool Retrack_ = false;

    bool DegInput_ = false;


public:

    QNApplication();

    void QNMainLoop();

    ~QNApplication();

    void QNMainEventHandler(SDL_Event);

    void QNScrollEventHandler (SDL_Event, QnViewPort, QNDekart&, int&, int&);

    void QNButtonEventHandler (SDL_Event, SDL_Rect,  CurveField&);

    void QNAddButtonEventHandler (SDL_Event, SDL_Rect, SDL_Rect);

    void QNMathButtonEventHandler (SDL_Event, SDL_Rect rect, QnEdit& input, char type);

};

