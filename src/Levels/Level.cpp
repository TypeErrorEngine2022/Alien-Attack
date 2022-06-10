#include "../../include/headers/Map/Level.h"

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
        m_layers[i] -> update();
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