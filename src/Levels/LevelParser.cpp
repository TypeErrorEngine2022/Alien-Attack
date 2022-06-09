#include "../../include/headers/Map/LevelParser.h"
#include "../../include/headers/Map/TileLayer.h"
#include "../../include/headers/Map/ObjectLayer.h"
#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/UtilsHeader/LoaderParams.h"
#include "../../include/headers/UtilsHeader/GameObjectFactory.h"
#include "../../include/headers/EntityHeader/GameObject.h"
#include "../../include/headers/UtilsHeader/base64.h"
#include "../../include/headers/Game.h"

#include <filesystem>
#include <string>
#include <algorithm>
#include <cmath>
#include <zlib.h>

LevelParser::LevelParser() : m_tileSize(0), m_width(0), m_height(0)
{
}

std::unique_ptr<Level> LevelParser::parseLevel(const char *levelFile)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLElement;

    XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    pLevel.reset(new Level);

    XMLElement *pRoot = levelDocument.RootElement();

    m_tileSize = pRoot->UnsignedAttribute("tilewidth");
    // width is horizontal in map, height is vertical
    m_width = pRoot->UnsignedAttribute("width");
    m_height = pRoot->UnsignedAttribute("height");

    for (XMLElement *e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == static_cast<std::string>("tileset"))
        {
            parseTilesets(e);
        }
        else if (e->Value() == static_cast<std::string>("layer"))
        {
            parseTileLayer(e);
        }
        else if (e->Value() == static_cast<std::string>("properties"))
        {
            parseTextures(e);
        }
        else if (e->Value() == static_cast<std::string>("objectgroup"))
        {
            parseObjectLayer(e);
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement *pTilesetRoot)
{
    std::vector<TileSet>& pTilesets = pLevel->getTilesets();

    // Assume source and map.tmx are in the same folder
    // convert the relative path of source to absolute path
    std::string currentDir = std::filesystem::current_path().string();
    std::string sourcePath = currentDir + "\\src\\assets\\Map\\" + pTilesetRoot->FirstChildElement()->Attribute("source");
    std::cout << "Tile source path:" << sourcePath << "\n";
    if (!TheTextureManager::Instance()->load(sourcePath, pTilesetRoot->Attribute("name"),
                                             TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load tilesets";
        return;
    }

    TileSet tileset;
    tileset.width = pTilesetRoot->FirstChildElement()->UnsignedAttribute("width");
    tileset.height = pTilesetRoot->FirstChildElement()->UnsignedAttribute("height");
    tileset.firstGridID = pTilesetRoot->UnsignedAttribute("firstgid");
    tileset.tileWidth = pTilesetRoot->UnsignedAttribute("tilewidth");
    tileset.tileHeight = pTilesetRoot->UnsignedAttribute("tileheight");
    tileset.spacing = pTilesetRoot->UnsignedAttribute("spacing");
    tileset.margin = pTilesetRoot->UnsignedAttribute("margin");
    tileset.name = pTilesetRoot->Attribute("name");

    tileset.numColumns = round(static_cast<double>((tileset.width - tileset.margin * 2)) /
                               (tileset.tileWidth + tileset.spacing));

    pTilesets.push_back(tileset);
    std::cout << "completed parsing tilesets\n";
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement *pTileElement)
{
    using tinyxml2::XMLElement;
    using tinyxml2::XMLNode;
    using tinyxml2::XMLText;

    std::vector<std::unique_ptr<Layer>>& pLayers = pLevel->getLayers();
    const std::vector<TileSet>& pTilesets = pLevel->getTilesets();

    std::unique_ptr<TileLayer> pTileLayer = std::make_unique<TileLayer>(m_tileSize, pTilesets);

    // tile data
    std::vector<std::vector<int>> data;

    std::string decodeIDs;
    XMLElement *pDataNode;

    bool collidable = false;

    for (XMLElement* e = pTileElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == static_cast<std::string>("properties"))
        {
            for (XMLElement* property = properties->FirstChildElement(); property != nullptr;
                     property = property->NextSiblingElement())
            {
                if (property->Value() == static_cast<std::string>("property"))
                {
                    if (property->Attribute("name") == static_cast<std::string>("Collidable"))
                    {
                        collidable = property->BoolAttribute("");
                    }
                }
            }
        }
        else if (e->Value() == static_cast<std::string>("data"))
        {
            pDataNode = e;
            break;
        }
    }

    std::string base64Text = pDataNode->GetText();
    base64Text.erase(std::remove_if(base64Text.begin(), base64Text.end(), isspace), base64Text.end());
    decodeIDs = base64_decode(base64Text);

    // uncompress zlib compression
    std::vector<int> gids(m_width * m_height);
    uLongf sizeOfGids = gids.size() * sizeof(int);
    // ZEXTERN int ZEXPORT uncompress OF((Bytef *dest,   uLongf *destLen,
    //                                      const Bytef *source, uLong sourceLen));
    int state = uncompress(reinterpret_cast<Bytef *>(&gids[0]), &sizeOfGids, reinterpret_cast<const Bytef *>(decodeIDs.c_str()),
                           decodeIDs.size());
    if (state != Z_OK)
    {
        std::cout << "failed to decompress zlib data\n";
    }
    std::cout << "Uncompressed the data\n";

    // each row has m_height cols
    std::vector<int> layerRow(m_width);

    for (std::size_t j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }

    for (std::size_t rows = 0; rows < m_height; rows++)
    {
        for (std::size_t cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }

    pTileLayer->SetTileIDs(data);

    pLayers.push_back(std::move(pTileLayer));

    std::cout << "complete parsing tileLayer\n";
}

void LevelParser::parseTextures(tinyxml2::XMLElement *pTextureRoot)
{
    using tinyxml2::XMLElement;

    for (XMLElement *e = pTextureRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == static_cast<std::string>("property"))
        {
            if (!TheTextureManager::Instance()->load(e->Attribute("value"), e->Attribute("name"),
                                                     TheGame::Instance()->getRenderer()))
            {
                std::cout << "failed to load textures";
            }
        }
    }
}

void LevelParser::parseObjectLayer(tinyxml2::XMLElement *pObjectElement)
{
    using tinyxml2::XMLElement;

    std::vector<std::unique_ptr<Layer>>& pLayers = pLevel->getLayers();

    std::unique_ptr<ObjectLayer> pObjectLayer = std::make_unique<ObjectLayer>();

    for (XMLElement *e = pObjectElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == static_cast<std::string>("object"))
        {
            int x, y, width, height, numFrames, callbackID, animSpeed;
            std::string textureID;

            // default to zero
            callbackID = animSpeed = 0;

            x = e->IntAttribute("x");
            y = e->IntAttribute("y");

            std::shared_ptr<GameObject> pGameObject =
                std::move(TheGameObjectFactory::Instance()->create(e->Attribute("type")));

            if (e->FirstChildElement()->Value() == static_cast<std::string>("properties"))
            {
                XMLElement *properties = e->FirstChildElement();
                for (XMLElement *property = properties->FirstChildElement(); property != nullptr;
                     property = property->NextSiblingElement())
                {
                    if (property->Value() == static_cast<std::string>("property"))
                    {
                        if (property->Attribute("name") == static_cast<std::string>("numFrames"))
                            numFrames = property->IntAttribute("value");

                        else if (property->Attribute("name") == static_cast<std::string>("textureHeight"))
                            height = property->IntAttribute("value");

                        else if (property->Attribute("name") == static_cast<std::string>("textureID"))
                            textureID = property->Attribute("value");

                        else if (property->Attribute("name") == static_cast<std::string>("textureWidth"))
                            width = property->IntAttribute("value");

                        else if (property->Attribute("name") == static_cast<std::string>("callbackID"))
                            callbackID = property->IntAttribute("value");

                        else if (property->Attribute("name") == static_cast<std::string>("animSpeed"))
                            animSpeed = property->IntAttribute("value");
                    }
                }
            }
            pGameObject->load(std::make_shared<LoaderParams>(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
            if (type == "Player")
            {
                pLevel->setPlayer(std::dynamic_pointer_cast<Player>(pSharedGameObject));
            }
            pObjectLayer->getGameObject().push_back(pGameObject);
        }
    }

    pLayers.push_back(std::move(pObjectLayer));
    std::cout << "complete parsing object layer\n";
}
