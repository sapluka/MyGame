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
        /*
        清屏
处理键盘事件，更新蛇头的位置和方向，后续我们还会在这个函数里更新蛇身体的位置
处理吃食物和更新网格的事件
绘制背景
绘制棋盘    
绘制蛇头
绘制蛇身体
绘制食物
呈现
        */
        SDL_SetRenderDrawColor(initManager.getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(initManager.getRenderer());
        

        drawManager.drawBackground(initManager.getRenderer());
        drawManager.drawBoard(initManager.getRenderer());
        //drawFood
        handleKeyBoardEvents();//update snake head's position and direction,later we will update snake body's position in this function as well
        
        drawManager.updateGrid();
        
        drawManager.drawSnakeBody(initManager.getRenderer());
        drawManager.drawSnakeHead(initManager.getRenderer());

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
                 
                }
            }

            
        }
    }

      int currentTime = SDL_GetTicks();
            
            if (currentTime - moveCounter >= snakeHead.getMoveTimer() ) {
                if(isPossibleMove())
                {
                    snakeHead.move();
                    handleEvents();//吃食物,创建Food,Body,更新网格
                    drawManager.updateBodyPosition();
                    drawManager.recordLastPosition();

                    moveCounter = currentTime; // Reset timer after moving
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
        drawManager.createFood(initManager.getRenderer());//在这之前都成功了，现在要么是createSnakeBody函数有问题，要么是drawSnakeBody函数有问题
        drawManager.createSnakeBody(initManager.getRenderer());
         drawManager.updateGrid();
    }
}






