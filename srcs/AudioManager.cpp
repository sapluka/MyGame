#include "AudioManager.h"

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}

void AudioManager::init()
{
    Mix_Chunk* hissChunk = Mix_LoadWAV(HISS_SOUND_PATH);
    if (hissChunk) {
        chunkCache.emplace("hiss", hissChunk);
    } else {
        SDL_Log("Failed to load hiss.wav: %s", Mix_GetError());
    }

    Mix_Music* bgmMusic = Mix_LoadMUS(MENU_BGM_PATH);
    if (bgmMusic) {
        bgmCache.emplace("menuBGM", bgmMusic);
    } else {
        SDL_Log("Failed to load menuBGM.mp3: %s", Mix_GetError());
    }
}

void AudioManager::playChunk(std::string fileName)
{
    auto it = chunkCache.find(fileName);
    if (it != chunkCache.end()) {
        Mix_PlayChannel(-1, it->second, 0);
    }
}

void AudioManager::playBGM(std::string fileName)
{
    auto it = bgmCache.find(fileName);
    if (it != bgmCache.end()) {
        Mix_PlayMusic(it->second, -1);
    }
}

void AudioManager::stopBGM()
{
    Mix_HaltMusic();
}

void AudioManager::cleanup()
{
    for (auto& pair : chunkCache) {
        Mix_FreeChunk(pair.second);
    }
    chunkCache.clear();

    for (auto& pair : bgmCache) {
        Mix_FreeMusic(pair.second);
    }
    bgmCache.clear();
}