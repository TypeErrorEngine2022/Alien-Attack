#include "../../include/headers/Game.h"

#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/UtilsHeader/InputHandler.h"
#include "../../include/headers/UtilsHeader/LoaderParams.h"
#include "../../include/headers/UtilsHeader/StateParser.h"

#include "../../include/headers/GamestateHeader/MainMenuState.h"
#include "../../include/headers/GamestateHeader/PlayState.h"
#include "../../include/headers/GamestateHeader/GameOverState.h"

#include "../../include/headers/EntityHeader/GameObject.h"
#include "../../include/headers/EntityHeader/MenuButton.h"
#include "../../include/headers/EntityHeader/AnimatedGraphic.h"

#include <iostream>

std::shared_ptr<GameOverState> GameOverState::s_pInstance = nullptr;

std::shared_ptr<GameOverState> GameOverState::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = std::shared_ptr<GameOverState>(new GameOverState);
        return s_pInstance;
    }
    return s_pInstance;
}

std::string GameOverState::getStateID() const
{
    return s_stateID;
}

void GameOverState::s_gameOverToMain()
{
    std::cout << "Go to Main\n";

    TheGame::Instance() -> getGameStateMachine() -> changeState(MainMenuState::Instance());
}

void GameOverState::s_restartPlay()
{
    TheGame::Instance() -> getGameStateMachine() -> changeState(std::make_shared<PlayState>());
}

void GameOverState::update()
{
    for (auto& gameObj: m_gameObjects)
    {
        gameObj -> update();
    }
}

void GameOverState::render()
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> draw();
    }
}

bool GameOverState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("C:/Users/jacky/Desktop/sdl_game/src/test.xml", s_stateID, m_gameObjects, m_textureIDList);
    
    if (m_callbacks.empty())
    {
        m_callbacks.push_back(nullptr);
        m_callbacks.push_back(s_gameOverToMain);
        m_callbacks.push_back(s_restartPlay);
    }

    setCallbacks(m_callbacks);
    
    /*if (!TheTextureManager::Instance() -> load("C:/Users/jacky/Desktop/sdl_game/src/assets/gameover.png",
                                                "gameovertext", TheGame::Instance() -> getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance() -> load("C:/Users/jacky/Desktop/sdl_game/src/assets/main.png",
                                                "mainbutton", TheGame::Instance() -> getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance() -> load("C:/Users/jacky/Desktop/sdl_game/src/assets/restart.png",
                                                "restartbutton", TheGame::Instance() -> getRenderer()))
    {
        return false;
    }

    std::unique_ptr<GameObject> gameOverText = std::make_unique<AnimatedGraphic>();
    gameOverText -> load(std::make_shared<LoaderParams>(200, 100, 190, 30, "gameovertext", 2, 0, 2));
    std::unique_ptr<GameObject> button1 = std::make_unique<MenuButton>();
    button1 -> load(std::make_shared<LoaderParams>(200, 200, 200, 80, "mainbutton", 3));
    std::unique_ptr<GameObject> button2 = std::make_unique<MenuButton>();
    button2 -> load(std::make_shared<LoaderParams>(200, 300, 200, 80, "restartbutton", 3));


    m_gameObjects.push_back(std::move(gameOverText));
    m_gameObjects.push_back(std::move(button1));
    m_gameObjects.push_back(std::move(button2));*/

    std::cout << "entering GameOverState\n";
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++)
    {
        //if the gameobjects are type MenuButton then assign a callback
        //based on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_gameObjects[i].get()))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i].get());
            pButton -> setCallback(callbacks[pButton -> getCallbackID()]);
            pButton = nullptr;
        }
    }
}
