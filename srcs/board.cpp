#include "board.h"
#include <stdexcept>

Board::Board(int w, int h) : width(w), height(h)
{
    if(width <= 0 || height <= 0)
        throw std::invalid_argument("Width and height must be positive integers.");
    //it is the first time i know resize()
   
}

int Board::getWidth() const
{
    return width;
}

int Board::getHeight() const
{
    return height;
}
