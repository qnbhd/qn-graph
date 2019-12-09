//
// Created by qnbhd on 06.12.2019.
//

#include <iostream>
#include "QNDekart.hpp"
#include "Widgets/QnButton.hpp"

QNDekart::~QNDekart() = default;

void QNDekart::Hide() {
    DrawAxis(QnAxisPos_, __SETTINGS_WHITE_COLOR);
}

void QNDekart::Redraw() {
    DrawAxis(QnAxisPos_);
    DrawNet({0xA8, 0xA8, 0xA8, 0xFF});
}

void QNDekart::SetPos(SDL_Point pos) {
    QnAxisPos_.x = pos.x;
    QnAxisPos_.y = pos.y;
}

SDL_Point QNDekart::GetPos() {
    return QnAxisPos_;
}

void QNDekart::DrawAxis(SDL_Point, SDL_Color color) {
    DrawLine(QnRenderer_, {QnAxisPos_.x, __APPLICATION_SIZE_HEIGHT}, {QnAxisPos_.x, 0},
             2, color);

    DrawLine(QnRenderer_, {0, QnAxisPos_.y}, {2 * __APPLICATION_SIZE_WIDTH / 3, QnAxisPos_.y},
             2, color);

}

void QNDekart::DrawLine(SDL_Renderer *renderer, SDL_Point from, SDL_Point to, int brushWidth, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, from.x, from.y, to.x, to.y);

    if (brushWidth <= 1)
        return;

    for (int i = 1; i <= brushWidth; ++i) {
        SDL_RenderDrawLine(renderer, from.x + i, from.y, to.x + i, to.y);
        if (from.y == to.y)
            SDL_RenderDrawLine(renderer, from.x, from.y + i, to.x, to.y + i);

        //SDL_RenderDrawLine( renderer, from.x-i, from.y, to.x-i, to.y );
    }

}

void QNDekart::DrawNet(SDL_Color color) {

    int curx = QnAxisPos_.x;

    /// Draw X-net
    QnButton Btn(QnRenderer_, std::string(" "),
                 {5, 5, 5, 5},
                 {0xFF, 0xFF, 0xFF, 0xFF}, {0x0, 0x0, 0x0, 0x0}, 11, -1);

    int start = 0;
    double dxy = CALCULATE_DXY(eps_);

    int j = 0;
    for (int i = 0; curx >= _NET_OFFSET_X; curx -= eps_, ++i) {
        DrawLine(QnRenderer_, {curx, 0}, {curx, __APPLICATION_SIZE_HEIGHT}, 1, color);
        Btn.SetPos({curx, QnAxisPos_.y});
        Btn.SetText(std::to_string(static_cast<int>(start - dxy * i)));
        Btn.Redraw();
        j = i;
    }

    std::string bf = std::to_string(static_cast<int>(start - dxy * j)) + " ";

    interval_.leftBound  = static_cast<int>(start - abs(dxy) * j - 5);

    j = 0;

    curx = QnAxisPos_.x;

    for (int i = 0; curx <= 2 * __APPLICATION_SIZE_WIDTH / 3; curx += eps_, ++i) {
        DrawLine(QnRenderer_, {curx, 0}, {curx, __APPLICATION_SIZE_HEIGHT}, 1, color);
        Btn.SetPos({curx, QnAxisPos_.y});
        Btn.SetText(std::to_string(static_cast<int>(start + dxy * i)));
        Btn.Redraw();
        j = i;
    }

    interval_.rightBound = static_cast<int>(start + dxy * j + 5);

    /// Draw Y-net

    int cury = QnAxisPos_.y;

    for (int i = 0; cury >= _NET_OFFSET_Y; cury -= eps_, ++i) {
        DrawLine(QnRenderer_, {0, cury}, {__APPLICATION_SIZE_HEIGHT, cury}, 1, color);
        Btn.SetPos({QnAxisPos_.x, cury});
        Btn.SetText(std::to_string(static_cast<int>(start + dxy * i)));
        Btn.Redraw();
    }

    cury = QnAxisPos_.y;

    for (int i = 0; cury <= __APPLICATION_SIZE_HEIGHT + _NET_OFFSET_Y; cury += eps_, ++i) {
        DrawLine(QnRenderer_, {0, cury}, {__APPLICATION_SIZE_HEIGHT, cury}, 1, color);
        Btn.SetPos({QnAxisPos_.x, cury});
        Btn.SetText(std::to_string(static_cast<int>(start - dxy * i)));
        Btn.Redraw();
    }

}

void QNDekart::SetEps(int eps) {
    eps_ = eps;
}

int QNDekart::GetEps() {
    return eps_;
}

QnInterval QNDekart::GetInterval() {
    return interval_;
}

SDL_Point QNDekart::DekartToScreen(double x, double y) {
    return {static_cast<int>(XDKS(x)), static_cast<int>(YDKS(y))};
}

void QNDekart::DekartToScreenPairs(const VectorPoints & source, VectorPoints & update) {
    update.clear();

    for (auto [x,y] : source)
    {
        auto res = DekartToScreen(x,y);
        update.emplace_back(res.x, res.y);
    }
}






