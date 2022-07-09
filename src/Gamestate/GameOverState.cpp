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
    
    TheGame::Instance()->getSoundManager()->playMusic("menubgm", -1);

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
