#include "../../include/headers/Map/Level.h"
#include "../../include/headers/Map/TileLayer.h"
#include "../../include/headers/Map/Layer.h"

#include "../../include/headers/UtilsHeader/TextureManager.h"

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
    for (std::size_t i = 0; i < m_layers.size(); i++)
    {
        m_layers[i] -> render();
    }
}

void Level::update()
{
    for (std::size_t i = 0; i < m_layers.size(); i++)
    {
        std::shared_ptr<Level> pLevel = shared_from_this();
        m_layers[i] -> update(pLevel);
    }
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