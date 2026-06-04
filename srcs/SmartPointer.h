#pragma once
#include "SDL_render.h"
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

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

struct TTF_FontDeleter {
    void operator()(TTF_Font* font) const {
        if (font) {
            TTF_CloseFont(font);
        }
    }
};

using SmartFont = std::unique_ptr<TTF_Font, TTF_FontDeleter>;


struct Mix_ChunkDeleter {
    void operator()(Mix_Chunk* chunk) const {
        if (chunk) {
            Mix_FreeChunk(chunk);
        }
    }
};


using SmartChunk = std::unique_ptr<Mix_Chunk, Mix_ChunkDeleter>;


struct Mix_MusicDeleter {
    void operator()(Mix_Music* music) const {
        if (music) {
            Mix_FreeMusic(music);
        }
    }
};

using SmartMusic = std::unique_ptr<Mix_Music, Mix_MusicDeleter>;