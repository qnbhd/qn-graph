//
// Created by qnbhd on 05.12.2019.
//

#pragma once

#include <string>
#include <SDL_system.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <utility>
#include "QNSETTINGS.hpp"

class QnTexture
{
public:
    //Initializes variables
    QnTexture();

    explicit QnTexture(SDL_Renderer *);

    //Deallocates memory
    ~QnTexture();

    //Loads image at specified path
    bool loadFromFile( const std::string& path );

//#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
    //Creates image from font string
    bool loadFromRenderedText( const std::string& textureText, SDL_Color textColor, int ptsize);
//#endif

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( SDL_Color );

    void setRenderer (SDL_Renderer *);

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    void setFontPath (std::string path)
    {
        font_ = std::move(path);
    }

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr,
                 SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    SDL_Renderer* QnRenderer_;

    //Image dimensions
    int mWidth;
    int mHeight;

    std::string font_ = __SETTINGS_MAIN_FONT_PATH;
};


