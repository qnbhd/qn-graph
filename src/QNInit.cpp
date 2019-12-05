//
// Created by qnbhd on 05.12.2019.
//

#include "QNInit.hpp"
#include "QNSETTINGS.hpp"

QNInit::QNInit() {
    auto result = SDLInit();
    if (!result) throw std::runtime_error( SDL_GetError() );
}

bool QNInit::SDLInit() {
    return SDL_Init( SDL_INIT_VIDEO ) >= 0 && WindowInit();
}

bool QNInit::WindowInit() {
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        std::cout << "Warning: Linear texture filtering not enabled!";
    }

    QnWindow_ = SDL_CreateWindow(QnWindowSettings);
    return (QnWindow_ != nullptr) && RenderInit();
}

bool QNInit::RenderInit() {
    QnRenderer_ = SDL_CreateRenderer( QnWindow_, -1,
                                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    return (QnRenderer_ != nullptr) && IMGInit();
}

bool QNInit::IMGInit() {
    SDL_SetRenderDrawColor( QnRenderer_, 0xFF, 0xFF, 0xFF, 0xFF );

    return (IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG) && TTFInit();
}

bool QNInit::TTFInit() {
    return (TTF_Init() != -1);
}

SDL_Window *QNInit::GetWindow() {
    return QnWindow_;
}

SDL_Renderer *QNInit::GetRenderer() {
    return QnRenderer_;
}

QNInit::~QNInit() {
    //Destroy window
    SDL_DestroyRenderer( QnRenderer_ );
    SDL_DestroyWindow( QnWindow_ );
    QnWindow_ = nullptr;
    QnRenderer_ = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}



