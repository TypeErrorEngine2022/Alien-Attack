#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "./GamestateHeader/GameState.h"
#include "./UtilsHeader/StateMachine.tpp"
#include "./UtilsHeader/SoundManager.h"


class Game
{
public:
    bool init(const char* title, int xpos, int ypos,
            int height, int width, int flags);
    void render();
    void update();
    void handleEvents();
    void clean();

    bool running();
    void quit();

    static Game* Instance();
    SDL_Renderer* getRenderer() const;
    std::shared_ptr<StateMachine<GameState>> getGameStateMachine();
    std::size_t getGameHeight() const;
    std::size_t getGameWidth() const;

    int getScrollSpeed() const;

    int getCurrentLevel() const;
    void setCurrentLevel(int currentLevel);
    bool getLevelComplete() const;

    int getPlayerLives() const;
    void setPlayerLives(int lives);

    std::shared_ptr<SoundManager> getSoundManager() const;
    
private:
    Game(){}

    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    
    std::size_t m_gameHeight;
    std::size_t m_gameWidth;
    
    int m_currentFrame;
    bool m_bRunning;

    int m_scrollSpeed;

    int m_playerLives;

    int m_currentLevel;
    bool m_bLevelComplete;

    std::shared_ptr<StateMachine<GameState>> m_pGameStateMachine;
    std::shared_ptr<SoundManager> m_pSoundManager;
};

typedef Game TheGame;