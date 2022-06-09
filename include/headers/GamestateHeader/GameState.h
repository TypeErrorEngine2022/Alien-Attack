#pragma once
#include "../EntityHeader/GameObject.h"
#include <vector>
#include <string>
#include <memory>

class GameState
{
public:
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit();

    virtual std::string getStateID() const = 0;

protected:
    std::vector<std::string> m_textureIDList;
    std::string s_stateID;
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};
