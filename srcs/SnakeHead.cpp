#include "SnakeHead.h"

void SnakeHead::move()//设置下一个位置和蛇头的矩形
{
    position.setX(position.getX() + dx);
    position.setY(position.getY() + dy);  
    headRect.x = INIT_POSX + position.getX() * TILE_SIZE;
    headRect.y = INIT_POSY + position.getY() * TILE_SIZE;
    headRect.w = TILE_SIZE;
    headRect.h = TILE_SIZE;
}

void SnakeHead::changeDirection(int newDx, int newDy)
{
    // Implementation for changing the snake head's direction
    dx = newDx;
    dy = newDy;
}

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