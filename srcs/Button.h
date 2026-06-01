#pragma once
#include "Widget.h"
#include "SmartPointer.h"
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <string>

enum class ButtonState
{
    NORMAL,
    HOVERED,
    PRESSED
};

class Button : public Widget
{
public:
    Button(int x, int y, int w, int h, const std::string& text, TTF_Font* font);
    ~Button() = default;

    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;

    void setOnClick(std::function<void()> callback);
    void activate();  // 键盘导航时直接触发回调
    void setSelected(bool sel);
    bool isSelected() const { return selected; }

private:
    ButtonState buttonState = ButtonState::NORMAL;
    std::string buttonText;
    std::function<void()> onClick;
    TTF_Font* font = nullptr;        // 不拥有所有权，由 Screen 管理
    bool selected = false;           // 键盘选中状态
    SmartTexture textTexture;        // 缓存的文字纹理
    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Color getBackgroundColor() const;
    void ensureTextTexture(SDL_Renderer* renderer);
};