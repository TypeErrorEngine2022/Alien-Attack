#pragma once
#include <string>

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