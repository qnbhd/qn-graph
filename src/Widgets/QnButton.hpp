//
// Created by qnbhd on 05.12.2019.
//

#pragma once

#include <SDL_system.h>
#include <string>
#include <utility>
#include "../QnObject.hpp"
#include "../QnTexture.hpp"

enum QnButtonState
{
    BUTTON_STATE_MOUSE_OUT = 0,
    BUTTON_STATE_MOUSE_OVER_MOTION = 1,
    BUTTON_STATE_MOUSE_DOWN = 2,
    BUTTON_STATE_MOUSE_UP = 3,
    BUTTON_STATE_TOTAL = 4
};

#define __TEXT_BTN_X_OFFSET 6
#define __TEXT_BTN_Y_OFFSET 6


class QnButton : public QnObject {
private:

    SDL_Renderer * QnRenderer_;

    std::string QnBtnText_;

    SDL_Rect QnBtnRect_;

    SDL_Color QnBtnColor_;

    SDL_Color QnBtnFontColor_;

    QnTexture QnBtnTexture_;

    Sint16 xoffset_;

    Sint16 yoffset_;

    Sint16 ptsize_;


public:

    QnButton (SDL_Renderer* renderer, std::string title, SDL_Rect rect, SDL_Color color,
                SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF}, Sint16 ptsize = 0,
                Sint16 xof = 0, Sint16 yof = 0) :
                QnRenderer_(renderer), QnBtnText_(std::move(title)), QnBtnRect_(rect), QnBtnColor_(color),
                QnBtnFontColor_(textColor),
                ptsize_(ptsize),
                xoffset_(xof),
                yoffset_(yof)
    {
        SDL_SetRenderDrawColor( QnRenderer_, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( QnRenderer_, &QnBtnRect_ );
        QnBtnTexture_.setRenderer(QnRenderer_);
        QnBtnTexture_.loadFromRenderedText(QnBtnText_, textColor, ptsize_);
        QnBtnTexture_.render(QnBtnRect_.x+__TEXT_BTN_X_OFFSET+xoffset_, QnBtnRect_.y+__TEXT_BTN_Y_OFFSET+yoffset_);
    }

    void Hide () override
    {
        SDL_SetRenderDrawColor( QnRenderer_, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderFillRect( QnRenderer_, &QnBtnRect_ );
    }

    void Redraw () override
    {
        SDL_SetRenderDrawColor( QnRenderer_, QnBtnColor_.r, QnBtnColor_.g, QnBtnColor_.b, 0xFF );
        SDL_RenderFillRect( QnRenderer_, &QnBtnRect_ );
        QnBtnTexture_.loadFromRenderedText(QnBtnText_, QnBtnFontColor_, ptsize_);
        QnBtnTexture_.render(QnBtnRect_.x+__TEXT_BTN_X_OFFSET+xoffset_, QnBtnRect_.y+__TEXT_BTN_Y_OFFSET+yoffset_);
    }

    void SetPos (SDL_Point pos) override
    {
        QnBtnRect_.x = pos.x;
        QnBtnRect_.y = pos.y;
    }

    SDL_Point GetPos () override
    {
        return {QnBtnRect_.x, QnBtnRect_.y};
    }

    SDL_Rect GetRect ()
    {
        return QnBtnRect_;
    }

    void SetText (std::string text)
    {
        QnBtnText_ = text;
    }

    void HandleEvent (SDL_Event e) override;


    ~QnButton () override
    = default;


};

