#include "DrawManager.h"
#include "InitManager.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "board.h"
#include "SnakeHead.h"
#include "food.h"
#include <vector>



void DrawManager::initGraphics(SDL_Renderer* renderer)
{
        boardTileTexture.reset(IMG_LoadTexture(renderer, BOARD_TILE_IMG_PATH)); 
        backgroundTexture.reset(IMG_LoadTexture(renderer, BACKGROUND_IMG_PATH));
        snakeHead.initHeadTexture(renderer);
        
    if (!boardTileTexture) {
        SDL_Log("Failed to load texture: %s", SDL_GetError());
    }

    if (!backgroundTexture) {
        SDL_Log("Failed to load texture: %s", SDL_GetError());
    }
    
    
}


void DrawManager::drawBoard(SDL_Renderer* renderer)
{
    for(int i=0;i<BOARD_WIDTH;i++)
    {
        for(int j=0; j<BOARD_HEIGHT;j++)
        {
           
            SDL_Rect rect{INIT_POSX+i*TILE_SIZE,INIT_POSY+j*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderCopy(renderer, boardTileTexture.get(), nullptr, &rect);

        }
    }
}

void DrawManager::drawSnakeHead(SDL_Renderer* renderer)
{
    SDL_Rect headRect{snakeHead.getHeadRect()};
    if(snakeHead.getDx()==1 &&snakeHead.getDy()==0)
    {
        SDL_RenderCopyEx(renderer, snakeHead.getHeadTexture(), nullptr, &headRect, 90, nullptr, SDL_FLIP_NONE);
       
    }
    else if(snakeHead.getDx()==-1 && snakeHead.getDy()==0)
    {
        SDL_RenderCopyEx(renderer, snakeHead.getHeadTexture(), nullptr, &headRect, 270, nullptr, SDL_FLIP_NONE);
       

    }
    else if(snakeHead.getDx()==0 && snakeHead.getDy()==1)
    {
        SDL_RenderCopyEx(renderer, snakeHead.getHeadTexture(), nullptr, &headRect, 180, nullptr, SDL_FLIP_NONE);
        
    }
    else if(snakeHead.getDx()==0 && snakeHead.getDy()==-1)
    {
        SDL_RenderCopyEx(renderer, snakeHead.getHeadTexture(), nullptr, &headRect, 0, nullptr, SDL_FLIP_NONE);
        
        
    }
     
}

void DrawManager::createSnakeBody(SDL_Renderer* renderer)//每次吃到食物时调用
{
    SDL_Log("CREATE SB");
    vec2 pos = snakeBodys.empty() ? snakeHead.getPosition() : snakeBodys.back()->getPosition();
    snakeBodys.emplace_back(std::make_unique<SnakeBody>(pos));
    snakeBodys.back()->initBodyTexture(renderer);
}

void DrawManager::recordLastPosition()
{
    lastHeadPosition = snakeHead.getPosition();   
}

void DrawManager::updateBodyPosition()//每帧调用，更新lastPositions，lastPositions里存储了每个蛇身体的上一个位置，在drawSnakeBody里根据lastPositions画出蛇身体
{
    if(snakeBodys.empty())
    {
        return;
    }
    //从后往前更新，保证读到的是前一段的旧位置
    for(size_t i=snakeBodys.size()-1; i>0; --i)
    {
        snakeBodys[i]->setPosition(snakeBodys[i-1]->getPosition());
    }
    snakeBodys[0]->setPosition(lastHeadPosition);
}

void DrawManager::deleteSnakeBody()//还没想好，maybe会有毒药
{
    //这就是不把lastPositions和snakeBodys放在snakeBody类里面的坏处，需要分别管理lastPositions和snakeBodysRects
    if(!snakeBodys.empty())
    {
        snakeBodys.pop_back();
    }


    if(!snakeBodyRects.empty())
    {
        snakeBodyRects.pop_back();
    }
}

void DrawManager::drawSnakeBody(SDL_Renderer* renderer)
{
    for(const auto& body : snakeBodys)
    {
        vec2 pos = body->getPosition();
        SDL_Rect bodyRect{INIT_POSX + pos.getX() * TILE_SIZE,
                          INIT_POSY + pos.getY() * TILE_SIZE,
                          TILE_SIZE, TILE_SIZE};
        SDL_RenderCopy(renderer, body->getBodyTexture(), nullptr, &bodyRect);
    }
}

void DrawManager::drawBackground(SDL_Renderer* renderer)
{
    SDL_Rect bgRect{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}; // Assuming the background covers the entire window
    SDL_RenderCopy(renderer, backgroundTexture.get(), nullptr, &bgRect); 
}


bool DrawManager::isEatSomething()
{
    SDL_Rect headR = snakeHead.getHeadRect();
    for (const auto& foodRect : foodRects)
    {
        if (SDL_HasIntersection(&foodRect, &headR))
        {
            return true;
        }
    }
    return false;
}


void DrawManager::initFoodTexture(SDL_Renderer* renderer)
{

}

void DrawManager::createFood(SDL_Renderer* renderer)
{
    //这里应该适用于所有的food
    std::vector<vec2>emptyPositions;
    for(int i=0;i<BOARD_WIDTH;i++)
    {
        for(int j=0;j<BOARD_HEIGHT;j++)
        {
            if(grid[j][i] == 0) // Check if the position is empty
            {
                emptyPositions.emplace_back(i, j);
            }
        }
    }

    if(emptyPositions.empty())
    {
        SDL_Log("No empty positions available for food!");
        return;
    }

    int index = rand() % emptyPositions.size();
    vec2 foodPosition = emptyPositions[index];

    //这里需要判断生成的食物位置是否合法，不能和蛇重叠
    if(!isPossibleFoodPosition(foodPosition))
    {
        createFood(renderer);
    }
    else {
        //这里的思路应该是先生成一个食物对象，（设置它的texture在类内操作，只决定生成什么类型的food）然后把它放到foods里，最后在drawFood里遍历foods，画出所有的食物
        foods.emplace_back(std::make_unique<Food>(foodPosition));
        foods.back()->initFoodTexture(renderer);
        foodRects.emplace_back(foods.back()->getFoodRect());
        //传入flag决定生成什么类型的food
        /*
        if(flag==0)
        {
            Food1 newFood();
            foods.emplace_back(newFood);

        }
        else if(flag==1)
        {
            Food2 newFood();
            foods.emplace_back(newFood);
        }
        else if(flag==2)
        {
            Food3 newFood();
            foods.emplace_back(newFood);
        }        
        
        
        */
    }

}

void DrawManager::drawFood(SDL_Renderer* renderer)
{
    if(foods.empty())
    {
        return;
    }
    for(const auto& foodRect : foodRects)
    {
        
        SDL_RenderCopy(renderer, foods.back()->getFoodTexture(), nullptr, &foodRect);
    }
}

bool DrawManager::isPossibleFoodPosition(const vec2 position) const
{
    if(grid[position.getY()][position.getX()] != 0) // Check if the position is not empty
    {
        return false; // Position is not valid for food
    }
    return true;
}

void DrawManager::updateGrid()
{
    //这里的思路是每次更新蛇头和蛇身体的位置时都调用这个函数，更新grid里对应位置的值，0表示空，1表示蛇头，2表示蛇身体，3表示食物
    //首先把grid里所有的位置都重置为0
    for(auto& row : grid)
    {
        std::fill(row.begin(), row.end(), 0);
    }

    //更新蛇头的位置
    grid[snakeHead.getPosition().getY()][snakeHead.getPosition().getX()] = 1;

    //更新蛇身体的位置
    for(const auto& body : snakeBodys)
    {
        grid[body->getPosition().getY()][body->getPosition().getX()] = 2;
    }

    //更新食物的位置
    for(const auto& food : foods)
    {
        vec2 foodPos = food->getFoodPosition();
        grid[foodPos.getY()][foodPos.getX()] = 3;
    }
}

void DrawManager::deleteFood()
{
    if(!foods.empty())
    {
        foods.pop_back();
    }

    if(!foodRects.empty())
    {
        foodRects.pop_back();
    }
}