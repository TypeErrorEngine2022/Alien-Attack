#pragma once
#include "Layer.h"
#include "Level.h"
#include <vector>
#include "../UtilsHeader/Vector2D.h"

class TileLayer: public Layer
{
public:
    TileLayer(std::size_t tileSize, const std::vector<TileSet>& tilesets);
    
    void update() override;
    void render() override;

    void SetTileIDs(const std::vector<std::vector<int>>& data);

    void setTileSize(int tileSize);

    //given id, find its corresponding tileset
    TileSet getTilesetByID(int tileID);

private:
    int m_numColumns;
    int m_numRows;
    std::size_t m_tileSize;

    Vector2D m_position;
    Vector2D m_velocity;

    //each tileset is a row of image from source, many rows form a tilelayer
    const std::vector<TileSet>& m_tilesets;

    //each tile has a ID
    std::vector<std::vector<int>> m_tileIDs;
};