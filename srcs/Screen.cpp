#include "Screen.h"

bool Screen::loadFont(const char* path, int fontSize)
{
    font.reset(TTF_OpenFont(path, fontSize));
    if (!font) {
        SDL_Log("Screen::loadFont failed: %s", TTF_GetError());
        return false;
    }
    return true;
}

Button* Screen::addButton(int x, int y, int w, int h, const std::string& text,
                          std::function<void()> onClick)
{
    auto btn = std::make_unique<Button>(x, y, w, h, text, font.get());
    btn->setOnClick(std::move(onClick));
    Button* ptr = btn.get();
    buttons.push_back(ptr);
    widgets.push_back(std::move(btn));

    // 第一个添加的按钮自动获得键盘焦点
    if (buttons.size() == 1) {
        selectedIndex = 0;
        updateSelection();
    }
    return ptr;
}

void Screen::render(SDL_Renderer* renderer)
{
    for (auto& widget : widgets) {
        widget->render(renderer);
    }
}

void Screen::handleEvent(const SDL_Event& event)
{
    // ── 键盘导航 ──
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                selectPrev();
                return;
            case SDLK_DOWN:
            case SDLK_s:
                selectNext();
                return;
            case SDLK_RETURN:
            case SDLK_KP_ENTER:
                activateSelected();
                return;
        }
    }

    // ── 鼠标事件：分发给所有 widget ──
    for (auto& widget : widgets) {
        widget->handleEvent(event);
    }

    // 鼠标移动时取消键盘选中（让用户可以在鼠标和键盘之间切换）
    if (event.type == SDL_MOUSEMOTION) {
        if (selectedIndex >= 0) {
            selectedIndex = -1;
            updateSelection();
        }
    }
}

void Screen::clearWidgets()
{
    widgets.clear();
    buttons.clear();
    selectedIndex = -1;
}

void Screen::selectNext()
{
    if (buttons.empty()) return;
    if (selectedIndex < 0) {
        selectedIndex = 0;
    } else {
        selectedIndex = (selectedIndex + 1) % static_cast<int>(buttons.size());
    }
    updateSelection();
}

void Screen::selectPrev()
{
    if (buttons.empty()) return;
    if (selectedIndex < 0) {
        selectedIndex = static_cast<int>(buttons.size()) - 1;
    } else {
        selectedIndex = (selectedIndex - 1 + static_cast<int>(buttons.size()))
                        % static_cast<int>(buttons.size());
    }
    updateSelection();
}

void Screen::activateSelected()
{
    if (selectedIndex >= 0 && selectedIndex < static_cast<int>(buttons.size())) {
        buttons[selectedIndex]->activate();
    }
}

void Screen::updateSelection()
{
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->setSelected(static_cast<int>(i) == selectedIndex);
    }
}