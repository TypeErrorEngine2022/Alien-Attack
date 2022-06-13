#pragma once

class Level;

#include <memory>

class Layer
{
public:
    virtual void render() = 0;
    virtual void update(std::shared_ptr<Level> pLevel) = 0;
    virtual void clean() = 0;
    virtual ~Layer(){} 
};