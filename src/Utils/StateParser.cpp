#include "../../include/headers/UtilsHeader/StateParser.h"
#include "../../include/headers/UtilsHeader/GameObjectFactory.h"
#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/Game.h"
#include <iostream>
#include <string>

bool StateParser::parseState(const char* stateFile, std::string stateID,
                            std::vector<std::unique_ptr<GameObject>>& pObjects,
                            std::vector<std::string>& pTextureIDs)
{
    using tinyxml2::XMLElement;
    using tinyxml2::XMLDocument;

    //create the XML document
    //when the doc is deleted, all other object will be deleted
    XMLDocument xmlDoc;

    //load the state file
    if (!xmlDoc.LoadFile(stateFile))
    {
        std::cerr << xmlDoc.ErrorStr() << "\n";
    }

    //get the root element
    XMLElement* pRoot = xmlDoc.RootElement();

    //pre declare the states root node
    XMLElement* pStateRoot = nullptr;
    //get this states root node and assign it to pStateRoot
    for (XMLElement* e = pRoot -> FirstChildElement(); e != nullptr; e = e -> NextSiblingElement())
    {
        if (e -> Value() == stateID)
        {
            pStateRoot = e;
        }
    }

    XMLElement* pTextureRoot = nullptr;

    for (XMLElement* e = pStateRoot -> FirstChildElement(); e != nullptr; e = e -> NextSiblingElement())
    {
        if (e -> Value() == static_cast<std::string>("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }

    //now parse the texture
    parseTextures(pTextureRoot, pTextureIDs);

    //pre declare the object root node
    XMLElement* pObjectRoot = nullptr;

    for (XMLElement* e = pStateRoot -> FirstChildElement(); e != nullptr; e = e -> NextSiblingElement())
    {
        if (e -> Value() == static_cast<std::string>("OBJECTS"))
        {
            pObjectRoot = e;
        }
    }

    //now parse the texture
    parseObjectRoot(pObjectRoot, pObjects);

    return true;
}

void StateParser::parseTextures(tinyxml2::XMLElement* pStateRoot, std::vector<std::string>& pTextureIDs)
{
    using tinyxml2::XMLElement;

    for (XMLElement* e = pStateRoot -> FirstChildElement(); e != nullptr; e = e -> NextSiblingElement())
    {
        std::string fileNameAttribute = e -> Attribute("filename");
        std::string idAttribute = e -> Attribute("ID");
        pTextureIDs.push_back(idAttribute);

        TheTextureManager::Instance() -> load(fileNameAttribute, idAttribute, TheGame::Instance() -> getRenderer());
    }
}

void StateParser::parseObjectRoot(tinyxml2::XMLElement* pStateRoot, std::vector<std::unique_ptr<GameObject>>& pObjects)
{
    using tinyxml2::XMLElement;

    for (XMLElement* e = pStateRoot -> FirstChildElement(); e != nullptr; e = e -> NextSiblingElement())
    {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        std::string textureID;

        x = e -> IntAttribute("x");
        y = e -> IntAttribute("y");
        width = e -> IntAttribute("width");
        height = e -> IntAttribute("height");
        numFrames = e -> IntAttribute("numFrames");
        callbackID = e -> IntAttribute("callbackID");
        animSpeed = e -> IntAttribute("animSpeed");

        textureID = e -> Attribute("textureID");

        std::unique_ptr<GameObject> pGameObject = TheGameObjectFactory::Instance() -> create(e -> Attribute("type"));
        pGameObject -> load(std::make_shared<LoaderParams>(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
        pObjects.push_back(std::move(pGameObject));
    }
}