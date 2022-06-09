#pragma once
#include <memory>
#include "../EntityHeader/GameObject.h"

class BaseCreator
{
public:
    virtual std::unique_ptr<GameObject> createGameObject() const = 0;
    virtual ~BaseCreator(){}
};
