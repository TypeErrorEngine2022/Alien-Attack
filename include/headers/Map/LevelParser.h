#pragma once
#include "Level.h"
#include "../UtilsHeader/tinyxml2.h"
#include <memory>
#include <vector>

class LevelParser
{
public:
    std::unique_ptr<Level> parseLevel(const char* levelFile);

private:
    LevelParser();

    void parseTilesets(tinyxml2::XMLElement* pTilesetRoot);
    
    void parseTileLayer(tinyxml2::XMLElement* pTilesetRoot);
    
    void parseTextures(tinyxml2::XMLElement* pTextureRoot);

    void parseObjectLayer(tinyxml2::XMLElement* pObjectElement);
    
    std::size_t m_tileSize;
    std::size_t m_width;
    std::size_t m_height;

    std::unique_ptr<Level> pLevel;
};