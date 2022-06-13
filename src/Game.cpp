#include "..\include\headers\Game.h"
#include "..\include\headers\UtilsHeader\TextureManager.h"
#include "../include/headers/UtilsHeader/Vector2D.h"
#include "../include/headers/UtilsHeader/InputHandler.h"
#include "../include/headers/UtilsHeader/StateMachine.h"

#include "../include/headers/GamestateHeader/MainMenuState.h"
#include "../include/headers/GamestateHeader/PlayState.h"

#include "../include/headers/UtilsHeader/GameObjectFactory.h"
#include "../include/headers/EntityHeader/Player.h"
#include "../include/headers/EntityHeader/Enemy.h"
#include "../include/headers/EntityHeader/MenuButton.h"
#include "../include/headers/EntityHeader/AnimatedGraphic.h"

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>

Game* Game::s_pInstance = nullptr;

Game* Game::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = new Game();
        return s_pInstance;
    }

    return s_pInstance;
}

SDL_Renderer* Game::getRenderer() const
{
    return m_pRenderer;
}

std::shared_ptr<StateMachine<GameState>> Game::getGameStateMachine()
{
    return m_pGameStateMachine;
}

std::size_t Game::getGameWidth() const
{
    return m_gameWidth;
}

std::size_t Game::getGameHeight() const
{
    return m_gameHeight;
}

int Game::getScrollSpeed() const
{
    return m_scrollSpeed;
}

bool Game::init (const char* title, int xpos, int ypos,
            int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL init success\n";
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        m_gameHeight = height;
        m_gameWidth = width;

        if (m_pWindow != nullptr)
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != nullptr)
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
            }
            else
            {
                std::cout << "renderer init fails\n";
                return false;
            }
        }
        else
        {
            std::cout << "window init fails\n";
            return false;
        }
    }
    else
    {
        std::cout << "SDL init fails\n";
        return false;
    }

    std::cout << "SDL init success\n";
    m_bRunning = true;

    m_scrollSpeed = 2;
    m_playerLives = 3;
    m_bLevelComplete = false;

    m_pGameStateMachine = StateMachine<GameState>::Instance();
    m_pGameStateMachine -> changeState(MainMenuState::Instance());

    TheGameObjectFactory::Instance() -> registerType("MenuButton", std::make_shared<MenuButtonCreator>());
    TheGameObjectFactory::Instance() -> registerType("Player", std::make_shared<PlayerCreator>());
    TheGameObjectFactory::Instance() -> registerType("Enemy", std::make_shared<EnemyCreator>());
    TheGameObjectFactory::Instance() -> registerType("AnimatedGraphic", std::make_shared<AnimatedGraphicCreator>());

    return true;
}

void Game::handleEvents()
{
    TheInputHandler::Instance() -> update();
}

void Game::update()
{
    m_pGameStateMachine -> update();   
}

int Game::getCurrentLevel() const
{
    return m_currentLevel;
}

void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    //m_pGameStateMachine -> changeState(new BetweenLevelState());
    m_bLevelComplete = false;
}

bool Game::getLevelComplete() const
{
    return m_bLevelComplete;
}

int Game::getPlayerLives() const
{
    return m_playerLives;
}

void Game::setPlayerLives(int lives)
{
    m_playerLives = lives;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    m_pGameStateMachine -> render();
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
    std::cout << "Starting cleaning\n";

    SDL_DestroyWindow(m_pWindow);

    // Every texture associated with renderer will be destroyed
    SDL_DestroyRenderer(m_pRenderer);

    m_pGameStateMachine -> clean();

    TheTextureManager::Instance() -> clean();
    
    InputHandler::Instance() -> clean();

    std::cout << "Release Game Instance\n";
    delete s_pInstance;
    s_pInstance = nullptr;

    
    SDL_Quit();
}

void Game::quit()
{
    m_bRunning = false;
}

bool Game::running()
{
    return m_bRunning;
}