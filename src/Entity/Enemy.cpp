#include "../../include/headers/EntityHeader/Enemy.h"
#include "../../include/headers/UtilsHeader/LoaderParams.h"
#include "../../include/headers/EntityHeader/ShooterObject.h"
#include <string>
#include <iostream>
#include <memory>

Enemy::Enemy() : ShooterObject() 
{

}

void Enemy::load(const std::shared_ptr<LoaderParams> pParams)
{
    ShooterObject::load(pParams);
    m_velocity.setY(2);
}

void Enemy::draw()
{
    ShooterObject::draw();
}

void Enemy::update()
{
    if (!m_bDying)
    {
        m_currentFrame = static_cast<int>((SDL_GetTicks64() / 100) % m_numFrames);

        if (m_position.getY() < 0)
        {
            m_velocity.setY(2);
        }
        else if (m_position.getY() > 400)
        {
            m_velocity.setY(-2);
        }

        ShooterObject::update();
    }
    else
    {
        ShooterObject::doDyingAnimation();
    }
}

std::string Enemy::type()
{
    return "Enemy";
}

void Enemy::collision()
{
    m_textureID = "largeexplosion";
    m_currentFrame = 0;
    m_numFrames = 10;
    m_width = 60;
    m_height = 60;
    m_bDying = true;
}

void Enemy::clean()
{
    std::cout << "cleaning Enemy\n";
}

Vector2D Enemy::getVelocity() const
{
    return m_velocity;
}

std::unique_ptr<GameObject> EnemyCreator::createGameObject() const
{
    return std::make_unique<Enemy>();
}