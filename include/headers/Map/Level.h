#pragma once

#include "TileSet.h"

#include "../EntityHeader/Player.h"

#include <string>
#include <vector>
#include <memory>

class Layer;
class TileLayer;


class Level: public std::enable_shared_from_this<Level>
{
public:
    ~Level(){};

    void update();
    void render();
    void clean();

    std::shared_ptr<Player> getPlayer();
    void setPlayer(std::shared_ptr<Player> player);

    std::vector<std::shared_ptr<TileLayer>>& getCollidableLayers();

private:
    Level();

    std::vector<TileSet> m_tilesets;
    std::vector<std::shared_ptr<Layer>> m_layers;
    std::vector<std::shared_ptr<TileLayer>> m_collisionLayers;

    std::vector<TileSet>& getTilesets();
    std::vector<std::shared_ptr<Layer>>& getLayers();

    std::shared_ptr<Player> m_player;
    std::vector<std::string> m_textureIDList;
    std::vector<std::string>& getTextureIDList();

    friend class LevelParser;
};