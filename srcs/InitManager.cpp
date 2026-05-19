#include "InitManager.h"
#include "SDL.h"
#include "SDL_video.h"
#include "SmartPointer.h"
#include "board.h"




void InitManager::initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_TIMER) < 0) 
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
}

void InitManager::initWindow()
{
    SmartWindow win {SDL_CreateWindow("MySnake", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE)};
    if(!win)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    this->win = std::move(win);
}

void InitManager::initRenderer()
{
    SmartRenderer renderer {SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_ACCELERATED)};
    if(!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    this->renderer = std::move(renderer);
}

void InitManager::initGame()
{
    initSDL();
    initWindow();
    initRenderer();
    
}

SDL_Renderer* InitManager::getRenderer() const
{
    return renderer.get();
}


