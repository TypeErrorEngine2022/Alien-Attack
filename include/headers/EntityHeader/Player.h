#pragma once
#include "ShooterObject.h"
#include "../UtilsHeader/LoaderParams.h"
#include "../UtilsHeader/BaseCreator.h"
#include "../UtilsHeader/Vector2D.h"
#include <string>
#include <memory>

class Player: public ShooterObject
{
public:
    Player();

    void load(const std::shared_ptr<LoaderParams> pParams);

    void draw() override;
    void update() override;
    void clean() override;

    void collision() override;

    Vector2D getVelocity() const;

private:
    void handleInput();
    void handleAnimation();

    //bring the player back if there are lives left
    void resurrect();

    bool m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

class PlayerCreator: public BaseCreator
{
public:
    std::unique_ptr<GameObject> createGameObject() const override;
};