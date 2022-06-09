#pragma once
#include <string>
#include <map>
#include <memory>
#include "../EntityHeader/GameObject.h"
#include "BaseCreator.h"

class GameObjectFactory
{
public:
    GameObjectFactory(const GameObjectFactory& rhs) = delete;
    GameObjectFactory(GameObjectFactory&& rhs) = delete;

    static std::shared_ptr<GameObjectFactory> Instance();

    bool registerType(std::string typeID, std::shared_ptr<BaseCreator> pCreator);
    std::unique_ptr<GameObject> create(std::string typeID);

private:
    GameObjectFactory(){}
    static std::shared_ptr<GameObjectFactory> s_pInstance;

    std::map<std::string, std::shared_ptr<BaseCreator>> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;