#pragma once
#include "DrawManager.h"
#include "SDL_rect.h"
#include "board.h"
#include "SnakeBody.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SnakeHead.h"
#include "SmartPointer.h"
#include "BackGround.h"
#include "Food.h"
#include <memory>
#include <vector>
#include "InitManager.h"


//the objects which are dynamically created better placed in the DrawManager
class DrawManager
{
    public:
        DrawManager(Board& b, SnakeHead& head): board(b), snakeHead(head)
        {            
        };
        ~DrawManager()=default;
        void initGraphics(SDL_Renderer* renderer);//init textures
        void drawBoard(SDL_Renderer* renderer);
        void drawSnakeHead(SDL_Renderer* renderer);

        bool isSnakeBodyEmpty() const
        {
            return snakeBodys.empty();
        }
        bool isFoodEmpty() const
        {
            return foods.empty();
        }


        void createSnakeBody(SDL_Renderer* renderer);
        void updateBodyPosition();//store positions in "lastPositions"
        void drawSnakeBody(SDL_Renderer* renderer);
        void deleteSnakeBody();

        void createFood(SDL_Renderer* renderer);
        void deleteFood();
        void drawFood(SDL_Renderer* renderer);
        void initFoodTexture(SDL_Renderer* renderer);
        bool isPossibleFoodPosition(const vec2 position) const;
        void updateGrid();
       
        bool isEatSomething();
        void drawBackground(SDL_Renderer* renderer);

        void rendererPresent(SDL_Renderer* renderer)
        {
            SDL_RenderPresent(renderer);
        }

        

    private:
        Board& board;
        SnakeHead& snakeHead;

        
        //说实话我真应该搞一个动态实例化的头文件，我现在不知道该怎么对动态实例化的对象操作
        std::vector<SDL_Rect>boardRects;
        std::vector<SDL_Rect>foodRects;
        std::vector<SDL_Rect>snakeBodyRects;

        std::vector<std::vector<int>> grid= std::vector<std::vector<int>>(board.getHeight(), std::vector<int>(board.getWidth(), 0));

        inline static std::vector<vec2> lastPositions;
        inline static std::vector<std::unique_ptr<SnakeBody>> snakeBodys;
        inline static std::vector<std::unique_ptr<Food>> foods;


        
        SmartTexture boardTileTexture;
        SmartTexture backgroundTexture;
        
};