//
// Created by qnbhd on 05.12.2019.
//

#include <fstream>
#include "QNApplication.hpp"
#include "Widgets/QnEdit.hpp"
#include "Linalg/Interpolation/Interpolation.hpp"
#include <ctime>

QNApplication::QNApplication()
{
    QnMainRenderer = QNi.GetRenderer();
    QnMainWindow = QNi.GetWindow();
    QnQuit = false;
    QNMainLoop();
}

void QNApplication::QNMainLoop() {
    //std::vector<CurveField> curveFields;
    QNDekart QnSC (QnMainRenderer, {__APPLICATION_SIZE_WIDTH / 3, __APPLICATION_SIZE_HEIGHT / 2});
    int dx, dy;




    //std::getline(std::cin, expression);
    MathParser mp;

    SDL_Event e;
    auto hided = false;
    int  eps = 40;


    QnViewPort QnViewPortFunc (0, 0, __APPLICATION_SIZE_WIDTH / 3,
                               __APPLICATION_SIZE_HEIGHT);

    QnViewPort QnViewPortGraph (__APPLICATION_SIZE_WIDTH / 3 + 1, 0, 2 * __APPLICATION_SIZE_WIDTH / 3,
                                __APPLICATION_SIZE_HEIGHT);

    QnButton addButton (QnMainRenderer, std::string("+"),
                               {__APPLICATION_SIZE_WIDTH / 6 - 20, __APPLICATION_SIZE_HEIGHT - 60, 40, 40},
                               __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                               __SETTINGS_WHITE_COLOR,18,8);

    QnButton approximationButton (QnMainRenderer, std::string("ap"),
                        {addButton.GetPos().x + 60, __APPLICATION_SIZE_HEIGHT - 60, 40, 40},
                        __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                        __SETTINGS_WHITE_COLOR,18,2);

    QnButton interpolationButton (QnMainRenderer, std::string("in"),
                                  {addButton.GetPos().x - 60, __APPLICATION_SIZE_HEIGHT - 60, 40, 40},
                                  __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                                  __SETTINGS_WHITE_COLOR,18,3);

    auto * TextBox1 = new QnEdit (QnMainRenderer, {5, 100, 210, 40}, QnViewPortFunc.ViewPort_,
            __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);


    auto * DelBtn1 = new QnButton (QnMainRenderer, std::string("x"),
                      {221, 100, 40, 40},
                      __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                      __SETTINGS_WHITE_COLOR,18,8);

    auto * TextBox2 = new QnEdit (QnMainRenderer, {5, 160, 210, 40}, QnViewPortFunc.ViewPort_,
                     __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);


    auto * DelBtn2 = new QnButton (QnMainRenderer, std::string("x"),
                      {221, 160, 40, 40},
                      __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                      __SETTINGS_WHITE_COLOR,18,8);


    QnTexture QnGraphLogo (QnMainRenderer);
    QnTexture BtnBack (QnMainRenderer);
    QnGraphLogo.loadFromFile(__SETTINGS_LOGO_PATH);
    BtnBack.loadFromFile(__SETTINGS_BACK_PATH);

    SDL_Rect x {0, 0, __APPLICATION_SIZE_WIDTH, __APPLICATION_SIZE_HEIGHT };


    curveFields.push_back({TextBox1, DelBtn1, 0});
    //curveFields.push_back({TextBox2, DelBtn2, 1});
    //editObjects.push_back(&TextBox2);

    srand(time(NULL));

    int pos = 0;
    while( !QnQuit ) {
        //SDL_RenderClear(qi.GetRenderer());
        //Handle events on queue
        dx = 0;
        dy = 0;

        while (SDL_PollEvent(&e) != 0) {
            QNMainEventHandler(e);
            QNScrollEventHandler(e, QnViewPortGraph, QnSC, dx, dy);

            //TextBox1.HandleEvent(e); TextBox2.HandleEvent(e);

            for (auto editBox : curveFields)
            {
                editBox.editbox->HandleEvent(e);
                editBox.button->HandleEvent(e);
                QNButtonEventHandler(e, QnViewPortFunc.ViewPort_, editBox);
            }

            addButton.HandleEvent(e);
            QNAddButtonEventHandler(e, addButton.GetRect(), QnViewPortFunc.ViewPort_);
            approximationButton.HandleEvent(e);
            interpolationButton.HandleEvent(e);
            QNMathButtonEventHandler(e, approximationButton.GetRect(),MathAction::APPROXIMATION_MNK);
            QNMathButtonEventHandler(e, interpolationButton.GetRect(),MathAction::INTERPOLATION);

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
        SDL_SetRenderDrawColor(QnMainRenderer, __SETTINGS_CURRENT_THEME_MAIN_COLOR_RD);
        SDL_RenderFillRect(QnMainRenderer, &QnViewPortFunc.ViewPort_ );


        for (auto a : curveFields) {
            a.button->Redraw();
            a.editbox->Redraw();
        }

        QnGraphLogo.render(0,0);
        BtnBack.render(0,__APPLICATION_SIZE_HEIGHT - 75);
        addButton.Redraw();
        approximationButton.Redraw();
        interpolationButton.Redraw();

        SDL_RenderSetViewport(QnMainRenderer, &QnViewPortGraph.ViewPort_ );
        SDL_SetRenderDrawColor(QnMainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        SDL_RenderFillRect(QnMainRenderer,  &x);

        QnSC.SetPos({QnSC.GetPos().x + dx, QnSC.GetPos().y + dy});

        QnSC.Redraw();


        auto [start, end] = QnSC.GetInterval();

        for (int i = 0; i < curveFields.size(); ++i) {
            try {
                auto expression = curveFields[i].editbox->GetText();
                if (expression != " ") {
                    mp.SetExpression(expression);
                    QnPlotter::Curve(QnMainRenderer, mp, QnSC, start, end, CurvesColor_[i%6]);
                }
            } catch (const std::runtime_error &e) {
                //// TODO CATCHING INVALID EXPRESSION
            } catch (const std::invalid_argument &e) {
                //// TODO CATCHING INVALID ARGUMENTS (division by zero, etc)
            } catch (const std::out_of_range &e) {
                //// TODO out of range (not needed , no throwing exception :) )
            }
        }

        QnPlotter::Points(QnMainRenderer, QnSC, appPoints, CurvesColor_[rand() % 6]);


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

void QNApplication::QNButtonEventHandler(SDL_Event e, SDL_Rect parent, CurveField& field) {
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        auto[btnposx, btnposy] = field.button->GetPos();

        if (x < btnposx || x > btnposx + field.button->GetRect().w || y < btnposy ||
            y > btnposy + field.button->GetRect().h)
            return;

        auto fieldId = std::find(curveFields.begin(), curveFields.end(), field);

        if (!Retrack_) {
            if (e.type == SDL_MOUSEBUTTONUP) {
                delete fieldId->button;
                fieldId->button = nullptr;
                delete fieldId->editbox;
                fieldId->editbox = nullptr;
                if (fieldId->points)
                    appPoints.clear();

                curveFields.erase(fieldId);
                Retrack_ = true;
                for (auto i = fieldId; i != curveFields.end(); ++i) {
                    i->button->SetPos(
                            {i->button->GetPos().x, i->button->GetPos().y - 60});
                    i->editbox->SetPos(
                            {i->editbox->GetPos().x, i->editbox->GetPos().y - 60});
                }

                if (curveFields.empty())
                {
                    auto * TextBox = new QnEdit (QnMainRenderer, {5, 100, 210, 40}, parent,
                                                 __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);


                    auto * DelBtn = new QnButton (QnMainRenderer, std::string("x"),
                                                  {221, 100, 40, 40},
                                                  __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                                                  __SETTINGS_WHITE_COLOR,18,8);

                    curveFields.push_back({TextBox, DelBtn, 0});
                }
            }



        } else
        {
            Retrack_ = false;
        }
    }
}

void QNApplication::QNAddButtonEventHandler(SDL_Event e, SDL_Rect rect, SDL_Rect parent) {
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        auto btnposx = rect.x;
        auto btnposy = rect.y;
        int py = 100 + 60*curveFields.size();

        if (x < btnposx || x > btnposx + rect.w || y < btnposy ||
            y > btnposy + rect.h)
            return;

        if (e.type == SDL_MOUSEBUTTONUP && curveFields.size() < 6)
        {

            auto * TextBox = new QnEdit (QnMainRenderer, {5, py, 210, 40}, parent,
                                          __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D, __SETTINGS_BLACK_COLOR, 18);


            auto * DelBtn = new QnButton (QnMainRenderer, std::string("x"),
                                           {221, py, 40, 40},
                                           __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D,
                                           __SETTINGS_WHITE_COLOR,18,8);

            curveFields.push_back({TextBox, DelBtn, 0});
        }
    }
}

void QNApplication::QNMathButtonEventHandler(SDL_Event e, SDL_Rect rect, char type) {
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        auto btnposx = rect.x;
        auto btnposy = rect.y;

        if (x < btnposx || x > btnposx + rect.w || y < btnposy ||
            y > btnposy + rect.h)
            return;

        Poly polynom;
        int deg = 0;

        if (e.type == SDL_MOUSEBUTTONUP)
        {
            auto filepath = QnFileDialog::FileDialog({{"txt", "Text file"}}, false);
            std::vector<std::pair<double, double>> pointsInput;
            std::ifstream fin (filepath);
            std::string str;
            fin >> str;

            if (str != __QN_FILE_MODIFICATOR)
                return;
            appPoints.clear();

            while (fin.good())
            {
                double _x, _y;
                fin >> _x >> _y;
                pointsInput.emplace_back(_x, _y);
                appPoints.emplace_back(_x, _y);
            }

            fin.close();

            if (pointsInput.empty())
                return;

            std::vector<double> X;
            std::vector<double> Y;
            std::vector<double> ans;

            for (auto obj : pointsInput) {
                auto[x, y] = obj;
                X.push_back(x);
                Y.push_back(y);
            }

            if (X.size() == 1)
                deg = 0;
            if (X.size() >= 2)
                deg = 2;
            if (X.size() >= 15)
                deg = 3;
            if (X.size() >= 30)
                deg = 4;

            switch (type) {
                case MathAction::APPROXIMATION_MNK: {
                    Approximation::MNK(X, Y, deg, ans, polynom);
                }
                break;
                case MathAction::INTERPOLATION: {
                    if (X.size() > 5)
                        return;
                    Interpolation::Lagranj(X, Y, ans, polynom);
                }
                break;
            }

            std::stringstream ss;
            ss << polynom;
            str = "y=" + ss.str();

            str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

            for (auto & curveField : curveFields) {
                curveField.points = 0;
                curveField.editbox->SetTextColor(__SETTINGS_BLACK_COLOR);
            }

            for (auto & curveField : curveFields) {
                if (curveField.editbox->GetText().size() <= 1) {
                    curveField.editbox->SetText(str);
                    curveField.editbox->SetTextColor(CurvesColor_[0]);
                    curveField.points = 1;
                    return;
                }
            }

            curveFields[0].editbox->SetText(str);
            curveFields[0].editbox->SetTextColor(CurvesColor_[0]);
            curveFields[0].points = 1;
            }

        }
}



QNApplication::~QNApplication() {
    for (auto obj: curveFields)
    {
        delete obj.editbox;
        delete obj.button;
    }
}




bool operator==(const CurveField &left, const CurveField &right) {
    return left.editbox == right.editbox;
}
