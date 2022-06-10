#pragma once
#include "ShooterObject.h"

#include "../UtilsHeader/LoaderParams.h"
#include "../UtilsHeader/Vector2D.h"

#include <string>
#include <memory>

class PlayerBullet: public ShooterObject
{
public:
    PlayerBullet();
    ~PlayerBullet(){}

    void load(const std::shared_ptr<LoaderParams> pParams, Vector2D heading);

    void draw() override;

    void update() override;

    void collision() override;

    std::string type() override;

private:
    Vector2D m_heading;
};

class EnemyBullet: public PlayerBullet
{
public:
    EnemyBullet();
    ~EnemyBullet(){}

    std::string type() override;

private:
    Vector2D m_heading;
};