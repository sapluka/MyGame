#include "GameManager.h"
#include "DrawManager.h"
#include "SDL_log.h"
#include "SnakeHead.h"

// ═══════════════════════════════════════════════════════════
//  初始化
// ═══════════════════════════════════════════════════════════

void GameManager::initGame()
{
    initManager.initGame();                        // SDL + Window + Renderer
    drawManager.initGraphics(initManager.getRenderer());  // 加载静态纹理
}

void GameManager::initScreens()
{
    SDL_Renderer* renderer = initManager.getRenderer();

    // 三个 screen 共用同一个字体
    menuScreen.loadFont(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE);
    pauseScreen.loadFont(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE);
    gameOverScreen.loadFont(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE);

    // ── 主菜单 ──
    menuScreen.addButton(500, 300, 200, 60, "Start Game", [this]() {
        resetGame();
        currentState = GameState::PLAYING;
    });
    menuScreen.addButton(500, 380, 200, 60, "Exit", [this]() {
        isRunning = false;
    });

    // ── 暂停 ──
    pauseScreen.addButton(500, 300, 200, 60, "Continue", [this]() {
        currentState = GameState::PLAYING;
    });
    pauseScreen.addButton(500, 380, 200, 60, "Return to Menu", [this]() {
        currentState = GameState::MENU;
    });

    // ── 死亡 ──
    gameOverScreen.addButton(500, 300, 200, 60, "Restart", [this]() {
        resetGame();
        currentState = GameState::PLAYING;
    });
    gameOverScreen.addButton(500, 380, 200, 60, "Return to Menu", [this]() {
        currentState = GameState::MENU;
    });
}

// ═══════════════════════════════════════════════════════════
//  主循环
// ═══════════════════════════════════════════════════════════

void GameManager::runGame()
{
    initGame();
    initScreens();

    SDL_Renderer* renderer = initManager.getRenderer();

    while (isRunning) {
        // ── 事件处理 ──
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                break;
            }

            switch (currentState) {
                case GameState::MENU:
                    menuScreen.handleEvent(event);
                    break;
                case GameState::PLAYING:
                    handlePlayingEvent(event);
                    break;
                case GameState::PAUSED:
                    handlePauseEvent(event);
                    break;
                case GameState::GAME_OVER:
                    gameOverScreen.handleEvent(event);
                    break;
            }
        }

        // ── 渲染 ──
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        drawManager.drawBackground(renderer);

        switch (currentState) {
            case GameState::MENU:
                menuScreen.render(renderer);
                break;

            case GameState::PLAYING:
                updateGame();
                renderGame();
                break;

            case GameState::PAUSED:
                renderGame();                    // 游戏画面垫底
                drawDimOverlay(renderer);        // 半透明遮罩
                pauseScreen.render(renderer);    // 按钮在上层
                break;

            case GameState::GAME_OVER:
                renderGame();
                drawDimOverlay(renderer);
                gameOverScreen.render(renderer);
                break;
        }

        SDL_RenderPresent(renderer);
    }
}

// ═══════════════════════════════════════════════════════════
//  状态事件处理
// ═══════════════════════════════════════════════════════════

void GameManager::handlePlayingEvent(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                currentState = GameState::PAUSED;
                break;
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
    }
}

void GameManager::handlePauseEvent(const SDL_Event& event)
{
    // ESC 也能恢复
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        currentState = GameState::PLAYING;
        return;
    }
    pauseScreen.handleEvent(event);
}

// ═══════════════════════════════════════════════════════════
//  游戏逻辑（从原来的 runGame 里拆出来）
// ═══════════════════════════════════════════════════════════

void GameManager::updateGame()
{
    handleMove();
    handleRecover();
    drawManager.updateGrid();
}

void GameManager::renderGame()
{
    drawManager.drawBoard(initManager.getRenderer());
    drawManager.drawSnakeHead(initManager.getRenderer());
    drawManager.drawSnakeBody(initManager.getRenderer());
    drawManager.drawFood(initManager.getRenderer());
}

void GameManager::handleMove()
{
    int currentTime = SDL_GetTicks();

    if (currentTime - moveCounter >= snakeHead.getMoveTimer()) {
        if (!isPossibleMove()) {
            currentState = GameState::GAME_OVER;   // 撞墙 → 死亡
            return;
        }

        snakeHead.move();
        handleEvents();                             // 吃食物, 创建 Food/Body, 更新网格
        drawManager.updateBodyPosition();
        drawManager.recordLastPosition();

        moveCounter = currentTime;
    }
}

void GameManager::handleEvents()
{
    if (drawManager.isFoodEmpty()) {
        drawManager.createFood(initManager.getRenderer());
    }

    if (drawManager.isEatSomething()) {
        SDL_Log("EAT FOOD");
        handleHiss();
        drawManager.deleteFood();
        drawManager.createFood(initManager.getRenderer());
        drawManager.createSnakeBody(initManager.getRenderer());
    }
}

void GameManager::handleHiss()
{
    if (drawManager.isEatSomething() && snakeHead.getState() == SnakeState::IDLE) {
        SDL_Log("HANDLE HISS");
        snakeHead.hiss();
        hissCounter = SDL_GetTicks();
    }
}

void GameManager::handleRecover()
{
    int currentTime = SDL_GetTicks();
    if (currentTime - hissCounter >= HISS_TIMER && snakeHead.getState() == SnakeState::HISS) {
        snakeHead.snakeRecover();
    }
}

bool GameManager::isPossibleMove()
{
    if (snakeHead.getPosition().getX() + snakeHead.getDx() < 0 ||
        snakeHead.getPosition().getX() + snakeHead.getDx() >= BOARD_WIDTH ||
        snakeHead.getPosition().getY() + snakeHead.getDy() < 0 ||
        snakeHead.getPosition().getY() + snakeHead.getDy() >= BOARD_HEIGHT) {
        return false;
    }
    return true;
}

// ═══════════════════════════════════════════════════════════
//  重置 & 辅助
// ═══════════════════════════════════════════════════════════

void GameManager::resetGame()
{
    // 重置蛇头
    snakeHead.setPosition(DEFAULT_POSX, DEFAULT_POSY);
    snakeHead.changeDirection(DEFAULT_DX, DEFAULT_DY);
    snakeHead.snakeRecover();

    // 清空蛇身
    while (!drawManager.isSnakeBodyEmpty()) {
        drawManager.deleteSnakeBody();
    }
    // 清空食物
    while (!drawManager.isFoodEmpty()) {
        drawManager.deleteFood();
    }

    // 重置计时器
    moveCounter = SDL_GetTicks();
    hissCounter = 0;

    // 刷新网格
    drawManager.updateGrid();
}

void GameManager::drawDimOverlay(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);   // 半透明黑色
    SDL_Rect overlay = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &overlay);
}