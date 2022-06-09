#include "../../include/headers/UtilsHeader/SoundManager.h"
#include <iostream>

std::shared_ptr<SoundManager> SoundManager::s_pInstance = nullptr;

std::shared_ptr<SoundManager> SoundManager::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = std::shared_ptr<SoundManager>(new SoundManager);
    }
    return s_pInstance;
}

SoundManager::SoundManager()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager()
{
    for (auto& [key, chunk]: m_sfxs)
    {
        Mix_FreeChunk(chunk);
    }

    for (auto& [key, music]: m_music)
    {
        Mix_FreeMusic(music);
    }

    Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
    if (type == SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());

        if (pMusic == nullptr)
        {
            std::cout << "Could not load music: ERROR - " << 
                            Mix_GetError() << "\n";
            return false;
        }

        m_music[id] = pMusic;
        return true;
    }
    else if (type == SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());

        if (pChunk == nullptr)
        {
            std::cout << "Could not load SFX: ERROR - " << 
                            Mix_GetError() << "\n";
            return false;
        }

        m_sfxs[id] = pChunk;
        return true;
    }

    return false;
}

void SoundManager::playSound(std::string id, int loop)
{
    //-1 indicates that play on any available channel
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::playMusic(std::string id, int loop)
{
    Mix_PlayMusic(m_music[id], loop);
}