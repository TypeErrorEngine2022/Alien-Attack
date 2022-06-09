#pragma once
#include "GameObject.h"
#include "../UtilsHeader/LoaderParams.h"
#include "../UtilsHeader/BaseCreator.h"
#include <memory>
#include <string>

class AnimatedGraphic: public GameObject
{
public:
    AnimatedGraphic();

    void load(const std::shared_ptr<LoaderParams> pParams) override;

    void draw() override;

    void update() override;

    void clean() override;

    void collision() override;

    std::string type() override;

    //other function uses base class function
};

class AnimatedGraphicCreator: public BaseCreator
{
public:
    std::unique_ptr<GameObject> createGameObject() const override;
};