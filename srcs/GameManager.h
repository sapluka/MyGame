#pragma once
#include "DrawManager.h"
#include "InitManager.h"
#include "SnakeHead.h"
#include "board.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

inline int moveCounter = 0;

class GameManager
{
    public:
        GameManager(InitManager& i, DrawManager& d, SnakeHead& s, Board& br): initManager(i), drawManager(d), snakeHead(s), board(br)
        {
            moveCounter = SDL_GetTicks();
        };
        ~GameManager()=default;
        void runGame();
        void handleKeyBoardEvents();
        void handleEvents();
        void initGame();
        bool isPossibleMove();
        
        

    private:
        InitManager& initManager;
        DrawManager& drawManager;
        SnakeHead& snakeHead;
        Board& board;

        
};