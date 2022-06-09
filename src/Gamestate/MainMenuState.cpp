#include "../../include/headers/GamestateHeader/MainMenuState.h"
#include "../../include/headers/Game.h"
#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/EntityHeader/GameObject.h"
#include "../../include/headers/EntityHeader/MenuButton.h"
#include "../../include/headers/GamestateHeader/PlayState.h"
#include "../../include/headers/UtilsHeader/StateParser.h"
#include <string>
#include <iostream>
#include <memory>


std::shared_ptr<MainMenuState> MainMenuState::s_pInstance = nullptr;

std::shared_ptr<MainMenuState> MainMenuState::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = std::shared_ptr<MainMenuState>(new MainMenuState);
    }
    return s_pInstance;
}

std::string MainMenuState::getStateID() const
{
    return s_stateID;
}

void MainMenuState::update()
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> update();
    }
}

void MainMenuState::render()
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> draw();
    }
}

bool MainMenuState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("C:/Users/jacky/Desktop/sdl_game/src/test.xml", s_stateID, m_gameObjects, m_textureIDList);
    
    if (m_callbacks.empty())
    {
        std::cout << "m_callbacks is empty\n";
        m_callbacks.push_back(0); // pushback 0 callbackID, so we can start from 1
        m_callbacks.push_back(s_menuToPlay);
        m_callbacks.push_back(s_exitFromMenu);
    }
    
    setCallbacks(m_callbacks);
    
    std::cout << "entering MainMenuState\n";
    return true;
}

void MainMenuState::s_menuToPlay()
{
    TheGame::Instance() -> getGameStateMachine() -> changeState(std::make_shared<PlayState>());
}

void MainMenuState::s_exitFromMenu()
{
    TheGame::Instance() -> quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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