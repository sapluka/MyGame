#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SmartPointer.h"


constexpr int WINDOW_WIDTH =1200;
constexpr int WINDOW_HEIGHT =800;

class InitManager
{
    public:
        InitManager()=default;
        ~InitManager();
        void initGame();
        void initSDL();
        void initWindow();
        void initRenderer();
        void initAudio();
        void shutdown();  // 清理所有 SDL 子系统，与 initSDL 对称
        SDL_Renderer* getRenderer() const;
    private:
        SmartWindow win;
        SmartRenderer renderer;

};