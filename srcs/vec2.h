#pragma once
#include "board.h"
#include <stdexcept>
class vec2
{
    public:
        vec2(int x, int y): x(x), y(y)
        {
         if(x<0||x>BOARD_WIDTH||y<0||y>BOARD_HEIGHT)
            throw std::invalid_argument("Position must be within the board boundaries.");
        }   

        int getX() const { return x; }
        int getY() const { return y; }
        void setX(int newX) { x = newX; }
        void setY(int newY) { y = newY; }
    private:
        int x;
        int y;
};