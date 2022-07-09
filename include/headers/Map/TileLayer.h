#pragma once
#include "Layer.h"
#include "TileSet.h"

#include <vector>
#include <memory>

#include "../UtilsHeader/Vector2D.h"

#include "../EntityHeader/Player.h"

class TileLayer: public Layer
{
public:
    TileLayer(std::size_t tileSize, const std::vector<TileSet>& tilesets);
    
    void update(std::shared_ptr<Level> pLevel) override;
    void render() override;
    void clean() override;

    void SetTileIDs(const std::vector<std::vector<int>>& data);

    void setTileSize(int tileSize);

    //given id, find its corresponding tileset
    TileSet getTilesetByID(int tileID);

    Vector2D getPosition() const;

    int getTileSize() const;
    int getNumTileRows() const;
    int getNumTileColumns() const;

private:
    int m_numScreenRows;
    int m_numScreenColumns;
    int m_numTileRows;
    int m_numTileColumns;
    std::size_t m_tileSize;

    Vector2D m_position;
    Vector2D m_velocity;

    //each tileset is a row of image from source, many rows form a tilelayer
    const std::vector<TileSet>& m_tilesets;

    //each tile has a ID
    std::vector<std::vector<int>> m_tileIDs;

    std::vector<std::vector<int>>& getTileIDs();
    
    friend void checkPlayerTileCollision(std::shared_ptr<Player> pPlayer,
                                         const std::vector<std::shared_ptr<TileLayer>>& collisionLayers);
};