//
// Created by qnbhd on 05.12.2019.
//

#include "QnEdit.hpp"

QnEdit::QnEdit(SDL_Renderer *renderer, SDL_Rect viewport, SDL_Rect parentviewport, SDL_Color color, SDL_Color textcolor, int ptsize) :
    QnRenderer_(renderer), QnEditViewPort_(viewport), QnParentViewPort_(parentviewport), QnEditText_(" "), QnEditColor_(color),
    QnEditTextColor_(textcolor), QnCursorPosition_(0), QnTextSize_(ptsize), QnFocusState_(QnEditState::UNFOCUSED), CamX_(0)
{
    SDL_RenderSetViewport(QnRenderer_, &QnEditViewPort_);
    QnEditTexture_.setRenderer(QnRenderer_);
    QnEditTexture_.setFontPath("misc/fonts/mono.ttf");
}


void QnEdit::Hide() {

}

void QnEdit::Redraw() {
    SDL_SetRenderDrawColor(QnRenderer_, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(QnRenderer_,  &QnEditViewPort_);

    SDL_RenderSetViewport(QnRenderer_, &QnEditViewPort_);
    SDL_SetRenderDrawColor(QnRenderer_, 0x0,0x0,0x0,0x0);

    if (QnFocusState_ == QnEditState::FOCUSED)
    {
        SDL_RenderDrawLine(QnRenderer_, static_cast<int>(QnTextSize_/2+_FONT_EPS) * QnCursorPosition_ - CamX_, _EDIT_OFFSET_Y-8,
                       static_cast<int>(QnTextSize_/2+_FONT_EPS) * QnCursorPosition_ - CamX_, QnEditViewPort_.h - 2);
    }

    QnEditTexture_.loadFromRenderedText(QnEditText_, QnEditTextColor_, QnTextSize_);
    QnEditTexture_.render(_EDIT_OFFSET_X - CamX_,_EDIT_OFFSET_Y);
    SDL_RenderSetViewport(QnRenderer_, &QnParentViewPort_);
}

void QnEdit::SetPos(SDL_Point pos) {
    QnEditViewPort_.x = pos.x;
    QnEditViewPort_.y = pos.y;
}

SDL_Point QnEdit::GetPos() {
    return {QnEditViewPort_.x, QnEditViewPort_.y};
}

void QnEdit::SetCursorPos(int pos) {
    //std::cout << pos << " " << QnEditText_.size() << std::endl;

    if (pos <= 0) {
        QnCursorPosition_ = pos = 0;
        return;
    } else if (pos > QnEditText_.size()) {
        QnCursorPosition_ = pos = QnEditText_.size();
        return;
    }

    QnCursorPosition_ = pos;
}

void QnEdit::HandleEvent(SDL_Event e) {
    if (QnFocusState_ == FOCUSED) {
        //std::cout << QnCursorPosition_ << std::endl;
        std::cout << CamX_ << std::endl;
        if( e.type == SDL_KEYDOWN )
        {
            if (e.key.keysym.sym == SDLK_RIGHT && QnEditText_ != " " && QnCursorPosition_ < QnEditText_.size() - 1) {
                if (QnCursorPosition_ >= (QnEditViewPort_.w / (QnTextSize_/2+_FONT_EPS))) {
                    CamX_ += (QnTextSize_ / 2 + _FONT_EPS);
                }
                SetCursorPos(QnCursorPosition_ + 1);
            }
            if (e.key.keysym.sym == SDLK_LEFT) {
                if (QnCursorPosition_ >= (QnEditViewPort_.w / (QnTextSize_ / 2 + _FONT_EPS)) && CamX_ >= 0)
                    CamX_ -= (QnTextSize_ / 2 + _FONT_EPS);
                SetCursorPos(QnCursorPosition_ - 1);
            }
            if (e.key.keysym.sym == SDLK_BACKSPACE) {
                if (QnEditText_.size() > 1 && QnCursorPosition_ > 0)
                {
                    QnEditText_.erase(QnCursorPosition_ - 1, 1);
                } else if (QnEditText_.size() == 1)
                {
                    QnEditText_ = " ";
                }
                if (QnCursorPosition_ >= (QnEditViewPort_.w / (QnTextSize_ / 2 + _FONT_EPS)) && CamX_ >= 0)
                    CamX_ -= (QnTextSize_ / 2 + _FONT_EPS);
                SetCursorPos(QnCursorPosition_-1);
            }
        }
        if (e.type == SDL_TEXTINPUT) {
            QnEditText_.insert(QnCursorPosition_, e.text.text);
            QnCursorPosition_++;
            if (QnCursorPosition_ >= (QnEditViewPort_.w / (QnTextSize_/2+_FONT_EPS)))
            {
                CamX_ += (QnTextSize_/2+_FONT_EPS);
            }
        }
    }

    if (CamX_ < 0)
        CamX_ = 0;

    if( e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);


        if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (x < QnEditViewPort_.x || x > QnEditViewPort_.x + QnEditViewPort_.w
                || y < QnEditViewPort_.y || y > QnEditViewPort_.y + QnEditViewPort_.h)
                QnFocusState_ = QnEditState::UNFOCUSED;
            else
                QnFocusState_ = QnEditState::FOCUSED;
        }

    }
}
