//
// Created by qnbhd on 05.12.2019.
//

#include "QnTexture.hpp"

QnTexture::QnTexture() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}


QnTexture::QnTexture(SDL_Renderer * renderer)
{
    //Initialize
    QnRenderer_ = renderer;
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void QnTexture::setRenderer(SDL_Renderer * renderer) {
    QnRenderer_ = renderer;
}

QnTexture::~QnTexture()
{
    //Deallocate
    free();
}

bool QnTexture::loadFromFile( const std::string& path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( QnRenderer_, loadedSurface );
        if( newTexture == nullptr )
        {
            std::cerr << SDL_GetError();
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != nullptr;
}

//#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool QnTexture::loadFromRenderedText( const std::string& textureText, SDL_Color textColor , int ptsize )
{
    //Get rid of preexisting texture
    free();

    //Render text surface

    auto QnFont_ = TTF_OpenFont(font_.c_str(), ptsize );
    if(!QnFont_) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended( QnFont_, textureText.c_str(), textColor );

    if( textSurface != nullptr )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( QnRenderer_, textSurface );
        if( mTexture == nullptr )
        {
            std::cerr << SDL_GetError();
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        TTF_CloseFont( QnFont_ );
        QnFont_ = nullptr;
        //Get rid of old surface
        SDL_FreeSurface( textSurface );

    }
    else
    {
        std::cerr << SDL_GetError();
    }


    //Return success
    return mTexture != nullptr;
}
//#endif

void QnTexture::free()
{
    //Free texture if it exists
    if( mTexture != nullptr )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void QnTexture::setColor( SDL_Color qC)
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, qC.r, qC.g, qC.b );
}

void QnTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void QnTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void QnTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( QnRenderer_, mTexture, clip, &renderQuad, angle, center, flip );
}

int QnTexture::getWidth()
{
    return mWidth;
}

int QnTexture::getHeight()
{
    return mHeight;
}


