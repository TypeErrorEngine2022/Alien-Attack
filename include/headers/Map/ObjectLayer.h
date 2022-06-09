#pragma once
#include "Layer.h"
#include "../EntityHeader/GameObject.h"
#include <vector>
#include <memory>

class ObjectLayer: public Layer
{
public:
    ObjectLayer();
    void update() override;
    void render() override;

    std::vector<std::shared_ptr<GameObject>>& getGameObject();

private:
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
};