#pragma once
#include "Widget.h"
#include "Button.h"
#include "SmartPointer.h"
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>
#include <functional>

constexpr int DEFAULT_FONT_SIZE = 28;
constexpr const char* DEFAULT_FONT_PATH = "../assets/font.ttf";

class Screen
{
public:
    Screen() = default;
    ~Screen() = default;

    // 禁止拷贝（unique_ptr 成员不可拷贝）
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

    void render(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event);

    // 字体管理
    bool loadFont(const char* path, int fontSize);
    TTF_Font* getFont() const { return font.get(); }

    // 添加按钮（返回裸指针方便外部操作，所有权归 Screen）
    Button* addButton(int x, int y, int w, int h, const std::string& text,
                      std::function<void()> onClick);

    void clearWidgets();

    // 键盘导航
    void selectNext();
    void selectPrev();
    void activateSelected();

private:
    std::vector<std::unique_ptr<Widget>> widgets;
    std::vector<Button*> buttons;       // 不拥有所有权，仅用于键盘导航
    SmartFont font;
    int selectedIndex = -1;

    void updateSelection();
};