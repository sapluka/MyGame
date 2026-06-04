#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioManager
{
    public:
        AudioManager()=default;
        ~AudioManager()=default;



        static AudioManager& getInstance();

        void playChunk(const char* filePath);
        void playBGM(const char* filePath);
        void stopBGM();
        void cleanup();


    private:
        AudioManager(const AudioManager&) = delete;
        AudioManager& operator=(const AudioManager&) = delete;
       
};