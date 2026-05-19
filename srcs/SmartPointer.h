#pragma once
#include "SDL_render.h"
#include <memory>
#include <SDL2/SDL.h>

struct SDL_WindowDeleter {
    void operator()(SDL_Window* window) const {
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
};

using SmartWindow = std::unique_ptr<SDL_Window, SDL_WindowDeleter>;

struct SDL_RendererDeleter {
    void operator()(SDL_Renderer* renderer) const {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
    }
};


using SmartRenderer = std::unique_ptr<SDL_Renderer,SDL_RendererDeleter>;


struct SDL_TextureDeleter {
    void operator()(SDL_Texture* texture) const {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
};

using SmartTexture = std::unique_ptr<SDL_Texture,SDL_TextureDeleter>;

