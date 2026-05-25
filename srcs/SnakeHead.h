#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL_render.h"
#include "Snake.h"
#include "vec2.h"
#include "SmartPointer.h"
#include "InitManager.h"


constexpr double DEFAULT_TIMER = 250;
constexpr int DEFAULT_VELOCITY = 5;
constexpr int DEFAULT_DX = 1;
constexpr int DEFAULT_DY = 0;
constexpr int DEFAULT_POSX = 4;
constexpr int DEFAULT_POSY = 4;
constexpr int HISS_TIMER = 100;

constexpr const char* SNAKE_HEAD_IMG_PATH = "../assets/snake_head_tile.png";
constexpr const char* SNAKE_HEAD_HISS_IMG_PATH = "../assets/snake_head_hiss_tile.png";

    
enum class SnakeState
{
    IDLE,
    HISS
};

class SnakeHead : public Snake
{
    public:
        SnakeHead()
        : velocity(DEFAULT_VELOCITY), dx(DEFAULT_DX), dy(DEFAULT_DY)
        {
            position.setX(DEFAULT_POSX);
            position.setY(DEFAULT_POSY);
            headRect.x = INIT_POSX + DEFAULT_POSX * TILE_SIZE;
            headRect.y = INIT_POSY + DEFAULT_POSY * TILE_SIZE;
            headRect.w = TILE_SIZE;
            headRect.h = TILE_SIZE;
            state = SnakeState::IDLE;

        }
        ~SnakeHead()=default;

        void move() override;
        void changeDirection(int dx, int dy) override;
        
        vec2 getPosition() const
        {
            return position;
        }

        vec2 getNextPosition() const
        {
            return vec2(position.getX() + dx, position.getY() + dy);
        }

        void setPosition(int x, int y)
        {
            position.setX(x);
            position.setY(y);
        }

        int getDx() const
        {
            return dx;
        }

        int getDy() const
        {
            return dy;
        }

        double getMoveTimer() const
        {
            return moveTimer;
        }

        double getHissTimer() const
        {
            return hissTimer;
        }

        void hiss();
        void snakeRecover();
        
        SnakeState getState() const
        {
            return state;
        }

        void initHeadTexture(SDL_Renderer* renderer);
        

        SDL_Rect getHeadRect() 
        {
            return headRect;
        }

        SDL_Texture* getHeadTexture()
        {
            return snakeHeadTexture.get();
        }

       
    private:
        int velocity;//to control the speed of the snake when using mouse motion
        double moveTimer = DEFAULT_TIMER;//to control the render time when using keyboard input
        double hissTimer = HISS_TIMER;//to control the render time of snake head's hiss state
        int dx;//to control the direction of the snake when using keyboard input
        int dy;//obviously,there must be a 0 between dx and dy
        SnakeState state;
        SDL_Rect headRect;
        SDL_Texture*IDLE_HEAD_TEXTURE;
        SDL_Texture*HISS_HEAD_TEXTURE;
        SmartTexture snakeHeadTexture;
        
        
};