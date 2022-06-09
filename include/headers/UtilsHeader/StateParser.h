#pragma once
#include <vector>
#include <string>
#include <memory>
#include "tinyxml2.h"
#include "../EntityHeader/GameObject.h"

class StateParser
{
public:
    bool parseState(const char* stateFile, std::string stateID,
                           std::vector<std::unique_ptr<GameObject>>& pObjects,
                            std::vector<std::string>& pTextureIDs);

private:
    void parseTextures(tinyxml2::XMLElement* pStateRoot, 
                        std::vector<std::string>& pTextureIDs);

    void parseObjectRoot(tinyxml2::XMLElement* pStateRoot, 
                        std::vector<std::unique_ptr<GameObject>>& pObjects);              
};