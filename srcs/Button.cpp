#include "Button.h"

Button::Button(int x, int y, int w, int h, const std::string& text, TTF_Font* f)
    : Widget(x, y, w, h), buttonText(text), font(f)
{
}

void Button::setOnClick(std::function<void()> callback)
{
    onClick = std::move(callback);
}

void Button::setSelected(bool sel)
{
    selected = sel;
}

void Button::activate()
{
    if (onClick) onClick();
}

SDL_Color Button::getBackgroundColor() const
{
    switch (buttonState) {
        case ButtonState::NORMAL:  return {60, 60, 60, 255};
        case ButtonState::HOVERED: return {90, 90, 90, 255};
        case ButtonState::PRESSED: return {140, 140, 140, 255};
    }
    return {60, 60, 60, 255};
}

void Button::ensureTextTexture(SDL_Renderer* renderer)
{
    // 只在第一次渲染时创建文字纹理（文字不变所以不需要重建）
    if (textTexture || !font) return;

    SDL_Surface* surface = TTF_RenderText_Blended(font, buttonText.c_str(), textColor);
    if (surface) {
        textTexture.reset(SDL_CreateTextureFromSurface(renderer, surface));
        SDL_FreeSurface(surface);
    }
}

void Button::render(SDL_Renderer* renderer)
{
    ensureTextTexture(renderer);

    // 1. 画背景矩形
    SDL_Color bg = getBackgroundColor();
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderFillRect(renderer, &widgetRect);

    // 2. 键盘选中时画金色边框
    if (selected) {
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
        SDL_RenderDrawRect(renderer, &widgetRect);
        SDL_Rect inner = {widgetRect.x + 1, widgetRect.y + 1,
                          widgetRect.w - 2, widgetRect.h - 2};
        SDL_RenderDrawRect(renderer, &inner);
    }

    // 3. 画居中文字
    if (textTexture) {
        int texW = 0, texH = 0;
        SDL_QueryTexture(textTexture.get(), nullptr, nullptr, &texW, &texH);
        SDL_Rect textRect = {
            widgetRect.x + (widgetRect.w - texW) / 2,
            widgetRect.y + (widgetRect.h - texH) / 2,
            texW, texH
        };
        
        SDL_RenderCopy(renderer, textTexture.get(), nullptr, &textRect);
    }

    
}

void Button::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION) {
        int x = event.motion.x;
        int y = event.motion.y;
        if (containsPoint(x, y)) {
            hovered = true;
            if (!pressed) {
                buttonState = ButtonState::HOVERED;
            }
        } else {
            hovered = false;
            buttonState = ButtonState::NORMAL;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;
        if (containsPoint(x, y)) {
            pressed = true;
            buttonState = ButtonState::PRESSED;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
        int x = event.button.x;
        int y = event.button.y;
        if (pressed && containsPoint(x, y)) {
            // 完整点击：按下和释放都在按钮内 → 触发回调
            if (onClick) onClick();
        }
        pressed = false;
        buttonState = hovered ? ButtonState::HOVERED : ButtonState::NORMAL;
    }
}