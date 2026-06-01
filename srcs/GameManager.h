#pragma once
#include "DrawManager.h"
#include "InitManager.h"
#include "SnakeHead.h"
#include "board.h"
#include "Screen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

enum class GameState
{
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class GameManager
{
public:
    GameManager(InitManager& i, DrawManager& d, SnakeHead& s, Board& br)
        : initManager(i), drawManager(d), snakeHead(s), board(br) {}
    ~GameManager() = default;

    void runGame();

private:
    InitManager& initManager;
    DrawManager& drawManager;
    SnakeHead& snakeHead;
    Board& board;

    GameState currentState = GameState::MENU;
    bool isRunning = true;

    // ── 计时器（从全局变量移入类成员）──
    int moveCounter = 0;
    int hissCounter = 0;

    // ── 三个界面 ──
    Screen menuScreen;
    Screen pauseScreen;
    Screen gameOverScreen;

    // ── 初始化 ──
    void initGame();
    void initScreens();

    // ── 状态分发 ──
    void handlePlayingEvent(const SDL_Event& event);
    void handlePauseEvent(const SDL_Event& event);

    // ── 游戏逻辑 ──
    void updateGame();
    void renderGame();
    void handleMove();
    void handleEvents();
    void handleHiss();
    void handleRecover();
    void resetGame();
    bool isPossibleMove();

    // ── 辅助 ──
    void drawDimOverlay(SDL_Renderer* renderer);
};