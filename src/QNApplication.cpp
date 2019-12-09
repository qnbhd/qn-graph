//
// Created by qnbhd on 05.12.2019.
//

#include "QNApplication.hpp"
#include "Widgets/QnEdit.hpp"

QNApplication::QNApplication()
{
    QnMainRenderer = QNi.GetRenderer();
    QnMainWindow = QNi.GetWindow();
    QnQuit = false;
    QNMainLoop();
}

void QNApplication::QNMainLoop() {
    std::vector<QnObject*> mObjects;
    //std::vector<QnEdit> lObjects;
    QNDekart QnSC (QnMainRenderer, {__APPLICATION_SIZE_WIDTH / 3, __APPLICATION_SIZE_HEIGHT / 2});
    int dx, dy;

    std::string expression = "sin(x)";
    //std::getline(std::cin, expression);
    MathParser mp;
    mp.SetExpression(expression);

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

    QnEdit TextBox1 (QnMainRenderer, {10, 100, 240, 40}, QnViewPortFunc.ViewPort_,
            __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);

    QnEdit TextBox2 (QnMainRenderer, {10, 160, 240, 40}, QnViewPortFunc.ViewPort_,
                     __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);

    QnEdit TextBox3 (QnMainRenderer, {10, 220, 240, 40}, QnViewPortFunc.ViewPort_,
                     __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);

    QnEdit TextBox4 (QnMainRenderer, {10, 280, 240, 40}, QnViewPortFunc.ViewPort_,
                     __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);

    QnEdit TextBox5 (QnMainRenderer, {10, 340, 240, 40}, QnViewPortFunc.ViewPort_,
                     __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);


    SDL_Rect x {0, 0, __APPLICATION_SIZE_WIDTH, __APPLICATION_SIZE_HEIGHT };


    mObjects.push_back(&NextBtn);
    mObjects.push_back(&PrevBtn);


    int pos = 0;
    while( !QnQuit ) {
        //SDL_RenderClear(qi.GetRenderer());
        //Handle events on queue
        dx = 0;
        dy = 0;

        while (SDL_PollEvent(&e) != 0) {
            QNMainEventHandler(e);
            QNScrollEventHandler(e, QnViewPortGraph, QnSC, dx, dy);

            TextBox1.HandleEvent(e); TextBox2.HandleEvent(e); TextBox3.HandleEvent(e); TextBox4.HandleEvent(e); TextBox5.HandleEvent(e);

            if( e.type == SDL_KEYDOWN ) {
               // if (e.key.keysym.sym == SDLK_RIGHT)
                //    TextBox1.SetCursorPos(++pos);
                //if (e.key.keysym.sym == SDLK_LEFT)
            //        TextBox1.SetCursorPos(--pos);
            }
        }

        SDL_SetRenderDrawColor( QnMainRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( QnMainRenderer);

        SDL_RenderSetViewport( QnMainRenderer, &QnViewPortFunc.ViewPort_ );
        SDL_SetRenderDrawColor(QnMainRenderer, __SETTINGS_CURRENT_THEME_LIGHT_COLOR_RD);
        SDL_RenderFillRect(QnMainRenderer, &QnViewPortFunc.ViewPort_ );

        for (auto obj: mObjects)
            obj->Redraw();

        TextBox1.Redraw(); TextBox2.Redraw(); TextBox3.Redraw(); TextBox4.Redraw(); TextBox5.Redraw();

        SDL_RenderSetViewport(QnMainRenderer, &QnViewPortGraph.ViewPort_ );
        SDL_SetRenderDrawColor(QnMainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        SDL_RenderFillRect(QnMainRenderer,  &x);

        QnSC.SetPos({QnSC.GetPos().x + dx, QnSC.GetPos().y + dy});

        QnSC.Redraw();

        // std::vector<SDL_Point> res = QnSC.DekartToScreenPairs(pts);

        //QnPlotter::Point(QnMainRenderer, pos.x, pos.y, __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D);
        //QnPlotter::Curve(QnMainRenderer, dekpts, __SETTINGS_CURRENT_THEME_ACCENT_DARK_COLOR_D);
        auto [start, end] = QnSC.GetInterval();
        //QnPlotter::Curve(QnMainRenderer, mp, QnSC, start, end, __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D);
        //QnPlotter::Curve(QnMainRenderer, QnSC, start, end, f, __SETTINGS_CURRENT_THEME_LIGHT_COLOR_D);

        try {
            mp.SetExpression(TextBox1.GetText());
            QnPlotter::Curve(QnMainRenderer, mp, QnSC, start, end, {0xAA, 0x01, 0xFF, 0x0});
        } catch (const std::runtime_error& e)
        {
            std::cout << "i can't read expr" << std::endl;
        } catch (const std::invalid_argument& e)
        {
            std::cout << "invalig argument :(" << std::endl;
        } catch (const std::out_of_range& e)
        {
            //std::cout << "blin" << std::endl;
        }

        try {
            mp.SetExpression(TextBox2.GetText());
            QnPlotter::Curve(QnMainRenderer, mp, QnSC, start, end, {0xAA, 0xFF, 0xA6, 0x0});
        } catch (const std::runtime_error& e)
        {
            std::cout << "i can't read expr" << std::endl;
        } catch (const std::invalid_argument& e)
        {
            std::cout << "invalig argument :(" << std::endl;
        } catch (const std::out_of_range& e)
        {
            //std::cout << "blin" << std::endl;
        }

        try {
            mp.SetExpression(TextBox3.GetText());
            QnPlotter::Curve(QnMainRenderer, mp, QnSC, start, end, {0xFF, 0x01, 0xAA, 0x0});
        } catch (const std::runtime_error& e)
        {
            std::cout << "i can't read expr" << std::endl;
        } catch (const std::invalid_argument& e)
        {
            std::cout << "invalig argument :(" << std::endl;
        } catch (const std::out_of_range& e)
        {
            //std::cout << "blin" << std::endl;
        }


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




