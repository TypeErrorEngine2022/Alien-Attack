#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "../UtilsHeader/LoaderParams.h"
#include "../UtilsHeader/BaseCreator.h"
#include "ShooterObject.h"


class Enemy: public ShooterObject
{
public:
    Enemy();
    virtual ~Enemy(){}
    
    void load(const std::shared_ptr<LoaderParams> pParams) override;

    void draw() override;
    void update() override;
    void clean() override;

    std::string type() override;

protected:
    int m_health;
};

class EnemyCreator: public BaseCreator
{
public:
    std::unique_ptr<GameObject> createGameObject() const override;
};