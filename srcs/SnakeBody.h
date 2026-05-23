#include "Snake.h"
#include "SnakeHead.h"
#include "vec2.h"
#include <vector>

constexpr const char* SNAKE_BODY_IMG_PATH = "../assets/snake_body_tile.png";

class SnakeBody : public Snake
{
    public:
        SnakeBody():Snake()
        {

        }
        ~SnakeBody()=default;        
        void updateBodyPosition();//set position
        const std::vector<vec2>& getLastPositions() const;
        vec2 getPosition() const
        {
            return position;
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