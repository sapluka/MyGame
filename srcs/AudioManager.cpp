#include <AudioManager.h>

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}

void AudioManager::playChunk(const char* filePath)
{
    Mix_Chunk* chunk = Mix_LoadWAV(filePath);
    if (!chunk) {
        SDL_Log("Failed to load sound effect: %s", Mix_GetError());
        return;
    }
    Mix_PlayChannel(-1, chunk, 0);
    Mix_FreeChunk(chunk); // 播放后立即释放
}

void AudioManager::playBGM(const char* filePath)
{
    Mix_Music* music = Mix_LoadMUS(filePath);
    if (!music) {
        SDL_Log("Failed to load background music: %s", Mix_GetError());
        return;
    }
    Mix_PlayMusic(music, -1); // 循环播放
}

void AudioManager::stopBGM()
{
    Mix_HaltMusic();
}