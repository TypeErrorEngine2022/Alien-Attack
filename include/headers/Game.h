#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "./GamestateHeader/GameState.h"
#include "./UtilsHeader/StateMachine.tpp"


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

    int getCurrentLevel() const;
    void setCurrentLevel(int currentLevel);
    
private:
    Game(){}

    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    
    std::size_t m_gameHeight;
    std::size_t m_gameWidth;
    
    int m_currentFrame;
    bool m_bRunning;

    int m_currentLevel;
    bool m_bLevelComplete;

    std::shared_ptr<StateMachine<GameState>> m_pGameStateMachine;
};

typedef Game TheGame;