//
// Created by qnbhd on 05.12.2019.
//

#include "QNApplication.hpp"

QNApplication::QNApplication()
{
    QnMainRenderer = QNi.GetRenderer();
    QnMainWindow = QNi.GetWindow();
    QnQuit = false;
    QNMainLoop();
}

void QNApplication::QNMainLoop() {
    std::vector<QnObject*> mObjects;
    QNDekart QnSC (QnMainRenderer, {__APPLICATION_SIZE_WIDTH / 3, __APPLICATION_SIZE_HEIGHT / 2});
    SDL_Rect QnCamera = { 0, 0, 2 * __APPLICATION_SIZE_WIDTH / 3, __APPLICATION_SIZE_HEIGHT };
    int dx, dy;

    SDL_Event e;
    auto hided = false;
    int  eps = 40;

    QnButton PrevBtn (QnMainRenderer, std::string(">"),
                      {60, 10, 40, 40},
                      __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                      __SETTINGS_WHITE_COLOR,18,7);

    QnButton NextBtn (QnMainRenderer, std::string("<"),
                      {10, 10, 40, 40},
                       __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                       __SETTINGS_WHITE_COLOR, 18, 7);


    QnViewPort QnViewPortFunc (0, 0, __APPLICATION_SIZE_WIDTH / 3,
                               __APPLICATION_SIZE_HEIGHT);

    QnViewPort QnViewPortGraph (__APPLICATION_SIZE_WIDTH / 3 + 1, 0, 2 * __APPLICATION_SIZE_WIDTH / 3,
                                __APPLICATION_SIZE_HEIGHT);

    SDL_Rect x {0, 0, __APPLICATION_SIZE_WIDTH, __APPLICATION_SIZE_HEIGHT };


    mObjects.push_back(&NextBtn);
    mObjects.push_back(&PrevBtn);


    int posx = __APPLICATION_SIZE_WIDTH/3, posy = __APPLICATION_SIZE_HEIGHT/2 - 50;

    std::vector<std::pair<int,int>> pts = {{1,1}, {2,2}, {3,3}, {4,4},{10,10},{11,21}};
    std::vector<std::pair<int,int>> dekpts;

    QnSC.DekartToScreenPairs(pts, dekpts);

    while( !QnQuit ) {
        //SDL_RenderClear(qi.GetRenderer());
        //Handle events on queue
        dx = 0;
        dy = 0;

        while (SDL_PollEvent(&e) != 0) {
            QNMainEventHandler(e);
            QNScrollEventHandler(e, QnViewPortGraph, QnSC, dx, dy);
        }


        SDL_SetRenderDrawColor( QnMainRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( QnMainRenderer);

        SDL_RenderSetViewport( QnMainRenderer, &QnViewPortFunc.ViewPort_ );
        SDL_SetRenderDrawColor(QnMainRenderer, __SETTINGS_CURRENT_THEME_LIGHT_COLOR_RD);
        SDL_RenderFillRect(QnMainRenderer, &QnViewPortFunc.ViewPort_ );

        for (auto obj: mObjects)
            obj->Redraw();

        SDL_RenderSetViewport(QnMainRenderer, &QnViewPortGraph.ViewPort_ );
        SDL_SetRenderDrawColor(QnMainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        SDL_RenderFillRect(QnMainRenderer,  &x);

        QnSC.SetPos({QnSC.GetPos().x + dx, QnSC.GetPos().y + dy});

        QnSC.Redraw();

        auto pos1 = QnSC.DekartToScreen(-6,2);
        auto pos2 = QnSC.DekartToScreen(1,3);

        QnSC.DekartToScreenPairs(pts, dekpts);
        // std::vector<SDL_Point> res = QnSC.DekartToScreenPairs(pts);

        //QnPlotter::Point(QnMainRenderer, pos.x, pos.y, __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D);
        //QnPlotter::Curve(QnMainRenderer, dekpts, __SETTINGS_CURRENT_THEME_ACCENT_DARK_COLOR_D);
        auto [start, end] = QnSC.GetInterval();
        QnPlotter::Curve(QnMainRenderer, QnSC, start-5, end+2, cos, __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D);
        QnPlotter::Curve(QnMainRenderer, QnSC, start-5, end+2, sin, __SETTINGS_CURRENT_THEME_LIGHT_COLOR_D);

        SDL_RenderPresent( QnMainRenderer);
    }
}

void QNApplication::QNMainEventHandler(SDL_Event e) {
        if (e.type == SDL_QUIT) {
            QnQuit = true;
        }
        if( e.type == SDL_KEYDOWN ) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                QnQuit = true;
            }
        }

}

void QNApplication::QNScrollEventHandler(SDL_Event e, QnViewPort QnGraphPort, QNDekart& QnSC, int& dx, int& dy) {
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEWHEEL )
    {
        int x, y, eps = QnSC.GetEps();
        SDL_GetMouseState(&x, &y);

        //auto ps = QnSC.DekartToScreen(6,5);//
       // std::cout << "(" << ps.x <<  " and " << x -  __APPLICATION_SIZE_WIDTH/3 << "), " <<
        //               "(" << ps.y << " and " << y << std::endl;


        if (x < QnGraphPort.ViewPort_.x || x > __APPLICATION_SIZE_WIDTH || y < 0 || y > __APPLICATION_SIZE_HEIGHT )
            return;

        // INSIDE

        switch(e.type)
        {
            case SDL_MOUSEMOTION:{
                if (ScrollState == QnScrollState::MOUSE_DOWN || ScrollState == MOUSE_DOWN_AND_MOVE)
                {
                    ScrollState = QnScrollState::MOUSE_DOWN_AND_MOVE;
                    dx = e.motion.xrel;
                    dy = e.motion.yrel;
                }
                //ScrollState = QnScrollState::;
            }
            break;

            case SDL_MOUSEBUTTONDOWN: {
                ScrollState = QnScrollState::MOUSE_DOWN;
            }
            break;

            case SDL_MOUSEBUTTONUP: {
                ScrollState = QnScrollState::NONE;
            }
            break;

            case SDL_MOUSEWHEEL:
                {
                    eps += 2*e.wheel.y;
                    if (eps < MINEPS)
                        eps = MINEPS;
                    if (eps > MAXEPS)
                        eps = MAXEPS;

                    QnSC.SetEps(eps);
                }
            break;
        }
    }



}

QNApplication::~QNApplication() {

}




