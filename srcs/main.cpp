#include <SDL.h>
#include "GameManager.h"

int main(int argc, char* argv[])
{
    Board board;
    SnakeHead snakeHead;
    InitManager initManager;
    DrawManager drawManager(board, snakeHead);
    GameManager gameManager(initManager, drawManager, snakeHead, board);
    gameManager.runGame();
    return 0;
}