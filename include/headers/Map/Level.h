#pragma once

#include "Layer.h"

#include <string>
#include <vector>
#include <memory>

struct TileSet
{
    int firstGridID;
    std::size_t tileWidth;
    std::size_t tileHeight;
    std::size_t spacing;
    std::size_t margin;
    std::size_t width;
    std::size_t height;
    std::size_t numColumns;
    std::string name;
};

class Level
{
public:
    ~Level(){};

    void update();
    void render();

    std::shared_ptr<Player> getPlayer();
    void setPlayer(std::shared_ptr<Player> player);

private:
    Level(){};
    std::vector<TileSet> m_tilesets;
    std::vector<std::unique_ptr<Layer>> m_layers;
    std::vector<std::unique_ptr<TileLayer>> m_collisionLayers;

    std::vector<TileSet>& getTilesets();
    std::vector<std::unique_ptr<Layer>>& getLayers();

    std::unique_ptr<Player> m_player;

    friend class LevelParser;
};