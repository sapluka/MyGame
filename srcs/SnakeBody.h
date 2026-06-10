#include "Snake.h"
#include "SnakeHead.h"
#include "vec2.h"
#include <vector>

#include "Assets.h"

class SnakeBody : public Snake
{
    public:
        SnakeBody(vec2 position):Snake()
        {
            this->position = position;
        }
        ~SnakeBody()=default;        
        void updateBodyPosition();//set position
        const std::vector<vec2>& getLastPositions() const;
        vec2 getPosition() const
        {
            return position;
        }

        void setPosition(const vec2& newPosition)
        {
            position = newPosition;
        }   

        SDL_Texture* getBodyTexture() const
        {
            return bodyTexture.get();
        }

        void initBodyTexture(SDL_Renderer* renderer)
        {
            bodyTexture.reset(IMG_LoadTexture(renderer, SNAKE_BODY_IMG_PATH)); 
            if (!bodyTexture) {
                SDL_Log("Failed to load texture: %s", SDL_GetError());
            }
        }
        // 必须实现基类的纯虚函数，否则它是一个抽象类，无法被实例化
        void move() override {}
        void changeDirection(int dx, int dy) override {}

    private:     

        SmartTexture bodyTexture;

};