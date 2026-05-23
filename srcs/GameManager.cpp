#include "GameManager.h"
#include "DrawManager.h"
#include "SDL_log.h"
#include "SnakeHead.h"

void GameManager::initGame()
{
    initManager.initGame();//init SDL, window and renderer
    drawManager.initGraphics(initManager.getRenderer());//init static textures
}



void GameManager::runGame()
{
    initGame();

    while (true) {
        //这里的逻辑有点乱
        SDL_SetRenderDrawColor(initManager.getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(initManager.getRenderer());
        handleKeyBoardEvents();//update snake head's position and direction,later we will update snake body's position in this function as well
        
        drawManager.drawBackground(initManager.getRenderer());
        drawManager.drawBoard(initManager.getRenderer());
        //drawFood
        drawManager.drawSnakeHead(initManager.getRenderer());
        drawManager.drawSnakeBody(initManager.getRenderer());
        handleEvents();
        drawManager.drawFood(initManager.getRenderer() );
        drawManager.rendererPresent(initManager.getRenderer());
        

    }
}

bool GameManager::isPossibleMove()
{
if(snakeHead.getPosition().getX()+snakeHead.getDx() < 0 || snakeHead.getPosition().getX()+snakeHead.getDx() >= BOARD_WIDTH ||
   snakeHead.getPosition().getY()+snakeHead.getDy() < 0 || snakeHead.getPosition().getY()+snakeHead.getDy() >= BOARD_HEIGHT) {
    return false;}
  
    return true; // Move is possible
}

void GameManager::handleKeyBoardEvents()//根据键盘事件改变蛇头的方向，同时根据蛇头的方向和位置更新蛇头的位置
{
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // Handle quit event, e.g., clean up and exit
            SDL_Quit();
            break;
        } 
        if (event.type == SDL_KEYDOWN) {
            // Handle key down event, e.g., change direction based on arrow keys
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    snakeHead.changeDirection(0, -1);
                    break;
                case SDLK_s:
                    snakeHead.changeDirection(0, 1);
                    break;
                case SDLK_a:
                    snakeHead.changeDirection(-1, 0);
                    break;
                case SDLK_d:
                    snakeHead.changeDirection(1, 0);
                    break;
            }
            if (event.type == SDL_WINDOWEVENT) 
            {
                if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    // Handle window resize event, e.g., adjust rendering parameters
                    //int newWidth = event.window.data1;
                    //int newHeight = event.window.data2;
                    
                    // You can use newWidth and newHeight to adjust your rendering logic
                }
            }

            
        }
    }

      int time2 = SDL_GetTicks();
            
            if (time2 - time1 >= snakeHead.getTimer() ) {
                if(isPossibleMove())
                {
                    snakeHead.move();
                    time1 = time2; // Reset timer after moving
                }
            }
}

void GameManager::handleEvents()//这个函数主要用来处理吃食物和更新网格的事件
{
    
    if(drawManager.isFoodEmpty())
    {
        drawManager.updateGrid();
        drawManager.createFood(initManager.getRenderer());
    }
    // This function can be used to handle the game events such as eating food, updating the grid, etc
    if(drawManager.isEatSomething())
    {
        SDL_Log("EAT FOOD");
        drawManager.deleteFood();//删除了food和foodrect
        drawManager.updateGrid();
        drawManager.createFood(initManager.getRenderer());
        drawManager.createSnakeBody(initManager.getRenderer());
         drawManager.updateGrid();
    }
}






