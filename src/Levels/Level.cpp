#include "../../include/headers/Map/Level.h"
#include "../../include/headers/Map/TileLayer.h"
#include "../../include/headers/Map/Layer.h"

#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/UtilsHeader/BulletHandler.h"

#include "../../include/headers/Game.h"

Level::Level()
{
    
}

std::vector<TileSet>& Level::getTilesets()
{
    return m_tilesets;
}

std::vector<std::shared_ptr<Layer>>& Level::getLayers()
{
    return m_layers;
}

std::vector<std::shared_ptr<TileLayer>>& Level::getCollidableLayers()
{
    return m_collisionLayers;
}

std::vector<std::string>& Level::getTextureIDList()
{
    return m_textureIDList;
}

void Level::render()
{
    //first render background layer, then gameobject layer or tilelayer
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++)
    {
        (*it)->render();
    }
    TheBulletHandler::Instance()->draw();
}

void Level::update()
{
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++)
    {
        std::shared_ptr<Level> pLevel = shared_from_this();
        (*it)->update(pLevel);
    }

    TheBulletHandler::Instance()->update();
}

void Level::clean()
{
    for (std::size_t i = 0; i < m_layers.size(); i++)
    {
        m_layers[i] -> clean();
    }

    for (std::size_t i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance() -> clearFromTextureMap(m_textureIDList[i]);
    }
}

std::shared_ptr<Player> Level::getPlayer()
{
    return m_player;
}

void Level::setPlayer(std::shared_ptr<Player> player)
{
    m_player = player;
}