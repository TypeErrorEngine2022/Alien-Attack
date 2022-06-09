#pragma once
#include <string>
#include <map>
#include <memory>
#include <SDL2/SDL_mixer.h>

enum sound_type
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
public:
    static std::shared_ptr<SoundManager> Instance();

    bool load(std::string fileName, std::string id, sound_type type);

    void playSound(std::string id, int loop);
    void playMusic(std::string id, int loop);

    ~SoundManager();

private:
    SoundManager();
    
    static std::shared_ptr<SoundManager> s_pInstance;

    //Sound Effect, multiple sound effects can be played at a time
    std::map<std::string, Mix_Chunk*> m_sfxs;

    //Music, can only play one music at a time
    std::map<std::string, Mix_Music*> m_music;

    SoundManager(const SoundManager& rhs);
    SoundManager& operator=(const SoundManager& rhs);
};

typedef SoundManager TheSoundManager;