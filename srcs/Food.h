#pragma once 
#include <vector>
#include "SDL_render.h"
#include "vec2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SmartPointer.h"



constexpr const char* FOOD_IMG_PATH = "../assets/food_tile.png";

class Food
{
    public:
        Food(vec2 pos): position(pos)
        {
            foodRect.x = INIT_POSX + position.getX() * TILE_SIZE;
            foodRect.y = INIT_POSY + position.getY() * TILE_SIZE;
            foodRect.w = TILE_SIZE;
            foodRect.h = TILE_SIZE;

        };
        virtual ~Food()=default;


        //我说实话只有下面的可以留下来
        virtual SDL_Rect getFoodRect() const
        {
            return foodRect;
        }

        virtual SDL_Texture * getFoodTexture() const
        {
            return foodTexture.get();
        }

        virtual void initFoodTexture(SDL_Renderer* renderer)
        {
            foodTexture.reset(IMG_LoadTexture(renderer, FOOD_IMG_PATH)); 
            if (!foodTexture) {
                SDL_Log("Failed to load texture: %s", SDL_GetError());
            }
        }

        virtual vec2 getFoodPosition() const
        {
            return position;
        }
    private:
        vec2 position;
        SmartTexture foodTexture;
        SDL_Rect foodRect={0,0,TILE_SIZE,TILE_SIZE};
        
};