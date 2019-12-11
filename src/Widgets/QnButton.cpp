//
// Created by qnbhd on 05.12.2019.
//

#include "QnButton.hpp"

void QnButton::HandleEvent(SDL_Event e) {
    //If mouse event happened
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < QnBtnRect_.x)
        {
            inside = false;
        }
            //Mouse is right of the button
        else if( x > QnBtnRect_.x + QnBtnRect_.w )
        {
            inside = false;
        }
            //Mouse above the button
        else if( y < QnBtnRect_.y )
        {
            inside = false;
        }
            //Mouse below the button
        else if( y > QnBtnRect_.y + QnBtnRect_.h )
        {
            inside = false;
        }

        //Mouse is outside button
        if( !inside )
        {
            QnBtnColor_ = __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D;
        }
            //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e.type )
            {
                case SDL_MOUSEMOTION:
                    QnBtnColor_ = __SETTINGS_CURRENT_THEME_ACCENT_COLOR_D;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    QnBtnColor_ = __SETTINGS_CURRENT_THEME_ACCENT_DARK_COLOR_D;
                    break;

                case SDL_MOUSEBUTTONUP:
                    QnBtnColor_ = __SETTINGS_CURRENT_THEME_ACCENT_LIGHT_COLOR_D;
                    break;
            }
        }
    }
}
