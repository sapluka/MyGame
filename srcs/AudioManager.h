#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <string>
#include "Assets.h"

class AudioManager
{
public:
    AudioManager() = default;
    ~AudioManager() { cleanup(); }

    static AudioManager& getInstance();

    // 加载所有音频资源（必须在 Mix_OpenAudio 之后调用）
    void init();

    void playChunk(std::string fileName);
    void playBGM(std::string fileName);
    void stopBGM();
    void cleanup();

private:
    std::unordered_map<std::string, Mix_Chunk*> chunkCache;
    std::unordered_map<std::string, Mix_Music*> bgmCache;
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
};