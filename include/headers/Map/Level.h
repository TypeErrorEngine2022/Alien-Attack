#pragma once

#include "TileSet.h"
#include "Layer.h"
#include "TileLayer.h"

#include "../EntityHeader/Player.h"

#include <string>
#include <vector>
#include <memory>


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
    std::vector<std::shared_ptr<Layer>> m_layers;
    std::vector<std::shared_ptr<TileLayer>> m_collisionLayers;

    std::vector<TileSet>& getTilesets();
    std::vector<std::shared_ptr<Layer>>& getLayers();

    std::vector<std::shared_ptr<TileLayer>>& getCollidableLayers();

    std::shared_ptr<Player> m_player;

    friend class LevelParser;
};