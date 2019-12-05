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

    SDL_Event e;
    auto hided = false;

    QnButton PrevBtn (QnMainRenderer, std::string(">"),
                      {60, 10, 40, 40},
                      {__SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, 0xFF}, 7);

    QnButton NextBtn (QnMainRenderer, std::string("<"),
                 {10, 10, 40, 40},
                 {__SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, 0xFF}, 7);



    mObjects.push_back(&NextBtn);
    mObjects.push_back(&PrevBtn);


    while( !QnQuit ) {
        //SDL_RenderClear(qi.GetRenderer());
        //Handle events on queue

        while (SDL_PollEvent(&e) != 0) {
            QNMainEventHandler(e);

            if( e.type == SDL_KEYDOWN ) {
                if (e.key.keysym.sym == SDLK_w) {
                    hided = !hided;
                }
            }
        }


        SDL_SetRenderDrawColor( QnMainRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( QnMainRenderer);

        QnViewPort QnViewPortFunc (0, 0, __APPLICATION_SIZE_WIDTH / 3,
                                   __APPLICATION_SIZE_HEIGHT);

        SDL_RenderSetViewport( QnMainRenderer, &QnViewPortFunc.ViewPort_ );
        SDL_SetRenderDrawColor(QnMainRenderer, __SETTINGS_CURRENT_THEME_LIGHT_COLOR_D, 0xFF);
        SDL_RenderFillRect(QnMainRenderer, &QnViewPortFunc.ViewPort_ );

        for (auto obj: mObjects)
            obj->Redraw();

        QnViewPort QnViewPortGraph (__APPLICATION_SIZE_WIDTH / 3 + 1, 0, 2 * __APPLICATION_SIZE_WIDTH / 3,
                                    __APPLICATION_SIZE_HEIGHT);

        SDL_RenderSetViewport(QnMainRenderer, &QnViewPortGraph.ViewPort_ );
        SDL_SetRenderDrawColor(QnMainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        SDL_Rect x {0, 0, 2 * __APPLICATION_SIZE_WIDTH / 3, __APPLICATION_SIZE_HEIGHT };
        SDL_RenderFillRect(QnMainRenderer,  &x);


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

QNApplication::~QNApplication() {

}


