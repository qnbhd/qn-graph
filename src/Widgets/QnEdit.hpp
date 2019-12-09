//
// Created by qnbhd on 05.12.2019.
//

#pragma once

#include "SDL_system.h"
#include "../QnTexture.hpp"
#include "../QnObject.hpp"
#include <string>

#define _EDIT_OFFSET_X 0
#define _EDIT_OFFSET_Y 10
#define _POS_OFFSET 5
#define _FONT_EPS 2


enum QnEditState
{
    FOCUSED,
    UNFOCUSED
};


class QnEdit : public QnObject {
private:

    SDL_Renderer * QnRenderer_;

    SDL_Rect QnEditViewPort_;

    SDL_Rect QnParentViewPort_;

    std::string QnEditText_;

    SDL_Color QnEditColor_;

    SDL_Color QnEditTextColor_;

    QnTexture QnEditTexture_;

    int QnCursorPosition_;

    int QnTextSize_;

    int QnFocusState_;

    int CamX_;


public:

    QnEdit(SDL_Renderer * renderer, SDL_Rect viewport, SDL_Rect parentvp, SDL_Color color, SDL_Color textcolor, int);

    void Hide() override;

    void SetCursorPos (int);

    void Redraw() override;

    void SetPos (SDL_Point) override ;

    SDL_Point GetPos () override;

    void HandleEvent (SDL_Event);

    std::string GetText ()
    {
        return QnEditText_;
    }


};
