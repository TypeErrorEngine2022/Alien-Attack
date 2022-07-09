#include "../../include/headers/Map/ObjectLayer.h"
#include "../../include/headers/Map/Level.h"

#include "../../include/headers/UtilsHeader/CollisionManager.h"

#include "../../include/headers/Game.h"

#include <string>
#include <iostream>

ObjectLayer::ObjectLayer():
    Layer()
{

}

std::vector<std::shared_ptr<GameObject>>& ObjectLayer::getGameObject()
{
    return m_gameObjects;
}

void ObjectLayer::update(std::shared_ptr<Level> pLevel)
{
    checkPlayerEnemyCollision(pLevel->getPlayer(), m_gameObjects);
    checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
    checkEnemyPlayerBulletCollision(m_gameObjects);

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();  )
    {
       if ((*it)->getPosition().getX() <= TheGame::Instance()->getGameWidth())
       {
            (*it)->setUpdating(true);
            (*it)->update();
       }
       else //out of current scene
       {   
            if ((*it)->type() != static_cast<std::string>("Player"))
            {
                (*it)->setUpdating(false);
                (*it)->scroll(TheGame::Instance()->getScrollSpeed());
            }
            else
            {
                //even if the player goes out of the scene
                //enable it to come back to the scene
                //Player should always be updating
                (*it)->update();
            }
       }

        // check if dead or off screen
        if((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheGame::Instance()->getGameHeight()) || ((*it)->dead()))
        {
            std::cout << "Deleted Gameobject: Out of Screen/Dead\n";
            it = m_gameObjects.erase(it); // erase from vector and get new iterator
        }
        else
        {
            ++it; // increment if all ok
        }
    }
}

void ObjectLayer::render()
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        if ((*it)->getPosition().getX() <= TheGame::Instance()->getGameWidth())
        {
            (*it)->draw();
        }
    }
}

void ObjectLayer::clean()
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> clean();
    }
}