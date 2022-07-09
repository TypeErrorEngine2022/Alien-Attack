#include "../../include/headers/Map/TileLayer.h"
#include "../../include/headers/Map/Level.h"

#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/Game.h"

#include "../../include/headers/GamestateHeader/GameOverState.h"

#include <iostream>
#include <memory>

TileLayer::TileLayer(std::size_t tileSize, const std::vector<TileSet>& tilesets):
    m_tileSize(tileSize), m_position(0.0, 0.0), m_velocity(0.0, 0.0), m_tilesets(tilesets)
{
    //Vertical is gamewidth => rows, Horizontal is gameheight => cols
    m_numScreenRows = TheGame::Instance() -> getGameWidth() / m_tileSize;
    m_numScreenColumns = TheGame::Instance() -> getGameHeight() / m_tileSize;
}

void TileLayer::update(std::shared_ptr<Level> pLevel)
{
    m_position += m_velocity;
    m_velocity.setX(1);
}

void TileLayer::render()
{
    int x, y, x2, y2;

    //Calculate where should the map be drawn from the tile ID array
    //eg. if m_position.getX() = 100, tilesize =32 => x = 3 => start drawing from column 3

    x = m_position.getX() / m_tileSize;
    y = m_position.getY() / m_tileSize;

    //ensure smooth scrolling of map, instead of jumping between tiles
    //use modulo to calculate the remaining tile amount that we need to move

    x2 = static_cast<int>(m_position.getX()) % m_tileSize;
    y2 = static_cast<int>(m_position.getY()) % m_tileSize;

    for (int i = 0; i < m_numScreenRows; i++)
    {
        for (int j = 0; j < m_numScreenColumns; j++)
        {      
            if (j + x >= m_numTileColumns)
            {
                std::cout << "exceed Level width.\n";
                TheGame::Instance()->getGameStateMachine()->changeState(GameOverState::Instance());
                break;
            }
            
            //only scroll the columns
            //j + x will exceed m_numScreenColumns, but not cols of m_tileIDs
            int id = m_tileIDs[i][j + x];

            if (id == 0)
            {
                // do not draw anything
                continue;
            }

            TileSet tileset = getTilesetByID(id);

            //count from zero
            id--;

            //subtract the firstGridID by 1 => 
            //allow us to treat each tilesheet the same and obtain the correct location
            //each row has tileset.numColumns, id / cols = current rows
            TheTextureManager::Instance() -> drawTile(tileset.name, tileset.margin, tileset.spacing, 
                                                        (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize,
                                                        m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns,
                                                        (id - (tileset.firstGridID - 1)) % tileset.numColumns,
                                                        TheGame::Instance() -> getRenderer());
        }
    }
}

void TileLayer::clean()
{
    
}

void TileLayer::SetTileIDs(const std::vector<std::vector<int>>& data)
{
    m_tileIDs = data;
    m_numTileRows = m_tileIDs.size();
    m_numTileColumns = m_tileIDs[0].size();
}

void TileLayer::setTileSize(int tileSize)
{
    m_tileSize = tileSize;
}

TileSet TileLayer::getTilesetByID(int tileID)
{
    for (std::size_t i = 0; i < m_tilesets.size(); i++)
    {
        //if i + 1 do not exceed m_tilesets
        if ( i + 1 <= m_tilesets.size() - 1)
        {
            if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
            {
                return m_tilesets[i];
            }
        }
        else
        {
            return m_tilesets[i];
        }
    }

    std::cout << "did not find tileset, returning empty tileset\n";
    TileSet t;
    return t;
}

std::vector<std::vector<int>>& TileLayer::getTileIDs()
{
    return m_tileIDs;
}

Vector2D TileLayer::getPosition() const
{   
    return m_position;
}

int TileLayer::getTileSize() const
{
    return m_tileSize;
}

int TileLayer::getNumTileRows() const
{
    return m_numTileRows;
}

int TileLayer::getNumTileColumns() const
{
    return m_numTileColumns;
}