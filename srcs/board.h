#pragma once
#include <vector>

constexpr int TILE_SIZE = 60;// Size of each tile in pixels
constexpr int BOARD_WIDTH = 10;// Number of tiles in the width
constexpr int BOARD_HEIGHT = 10; // Number of tiles in the height
constexpr int INIT_POSX = 300;
constexpr int INIT_POSY = 100;

constexpr const char* BOARD_TILE_IMG_PATH = "../assets/board_tile.png";

class Board
{
    public:
        Board(int w = BOARD_WIDTH, int h = BOARD_HEIGHT);
        int getWidth() const;
        int getHeight() const;
       
       
    private:
        int width;
        int height;
 
};