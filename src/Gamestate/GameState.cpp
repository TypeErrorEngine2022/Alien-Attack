#include "../../include/headers/GamestateHeader/GameState.h"
#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/UtilsHeader/InputHandler.h"
#include <iostream>

bool GameState::onExit()
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> clean();
    }

    m_gameObjects.clear(); // object in std::share_ptr will be destroyed

    for (std::size_t i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance() -> clearFromTextureMap(m_textureIDList[i]);
    }

    TheInputHandler::Instance() -> reset();
    std::cout << "exiting " << s_stateID << '\n';
    return true;
}