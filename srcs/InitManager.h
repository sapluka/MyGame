#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SmartPointer.h"


constexpr int WINDOW_WIDTH =1200;
constexpr int WINDOW_HEIGHT =800;

class InitManager
{
    public:
        InitManager()=default;
        ~InitManager()=default;
        void initGame();
        void initSDL();
        void initWindow();//create window and assign it to the member variable win
        void initRenderer();//create renderer and assign it to the member variable renderer
        void initAudio();
        SDL_Renderer* getRenderer() const;
    private:
        SmartWindow win;//这两个不需要加&，因为它们就是在这个类里创建的，不需要外部传入
        SmartRenderer renderer;
        
};