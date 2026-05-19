#pragma once
#include <string>
#include "vec2.h"
class Snake
{
    public:
        Snake();
        virtual ~Snake()=default;
        virtual void move()=0;
        virtual void changeDirection(int dx, int dy);//这个应该改掉
        std::string getDirection() const;
    protected:
        vec2 position;
};