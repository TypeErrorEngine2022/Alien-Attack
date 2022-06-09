#include "../../include/headers/Map/ObjectLayer.h"

ObjectLayer::ObjectLayer():
    Layer()
{

}

std::vector<std::shared_ptr<GameObject>>& ObjectLayer::getGameObject()
{
    return m_gameObjects;
}

void ObjectLayer::update()
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> update();
    }
}

void ObjectLayer::render()
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> draw();
    }
}