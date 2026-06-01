#pragma once
#include "SmartPointer.h"
#include <SDL2/SDL.h>

class Widget
{
public:
    Widget(int x, int y, int w, int h);
    virtual ~Widget() = default;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void handleEvent(const SDL_Event& event) = 0;

    // 几何判断：坐标 (x,y) 是否落在控件区域内
    bool containsPoint(int x, int y) const;

    // 状态查询
    bool isHovered() const { return hovered; }
    bool isPressed() const { return pressed; }

    const SDL_Rect& getRect() const { return widgetRect; }

protected:
    SDL_Rect widgetRect;
    bool hovered = false;
    bool pressed = false;
};