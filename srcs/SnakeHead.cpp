#include "SnakeHead.h"

void SnakeHead::move()//set next position
{
    position.setX(position.getX() + dx);
    position.setY(position.getY() + dy);  
}

void SnakeHead::changeDirection(int newDx, int newDy)
{
    // Implementation for changing the snake head's direction
    dx = newDx;
    dy = newDy;
}

/*模拟一次main里面的：
SDL_Event event;
while(SDL_PollEvent(&event))
{
    if(event.type == SDL_QUIT)
    {
        // Handle quit event
    }
    else if(event.type == SDL_KEYDOWN)
    {
        // Handle key down event, e.g., change direction based on arrow keys
        switch(event.key.keysym.sym)
        {
            case SDLK_W:
                changeDirection(0, -1);
                break;
            case SDLK_S:
                changeDirection(0, 1);
                break;
            case SDLK_A:
                changeDirection(-1, 0);
                break;
            case SDLK_D:
                changeDirection(1, 0);
                break;
        }
    }
}




*/

void SnakeHead::initHeadTexture(SDL_Renderer* renderer)
{
    IDLE_HEAD_TEXTURE = IMG_LoadTexture(renderer, SNAKE_HEAD_IMG_PATH);
    BITE_HEAD_TEXTURE = IMG_LoadTexture(renderer, SNAKE_HEAD_BITE_IMG_PATH);
    if (!IDLE_HEAD_TEXTURE) {
        SDL_Log("Failed to load idle snake head texture: %s", SDL_GetError());
    }
    if (!BITE_HEAD_TEXTURE) {
        SDL_Log("Failed to load bitten snake head texture: %s", SDL_GetError());
    }
    snakeHeadTexture.reset(IDLE_HEAD_TEXTURE);
}