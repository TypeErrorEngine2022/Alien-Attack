#include "../../include/headers/EntityHeader/Bullet.h"

PlayerBullet::PlayerBullet(): ShooterObject()
{

}

std::string PlayerBullet::type()
{
    return "PlayerBullet";
}

void PlayerBullet::load(const std::shared_ptr<LoaderParams> pParams, Vector2D heading)
{
    ShooterObject::load(pParams);
    m_heading = heading;
}

void PlayerBullet::draw()
{
    ShooterObject::draw();
}

void PlayerBullet::update()
{
    m_velocity.setX(m_heading.getX());
    m_velocity.setY(m_heading.getY());
    
    ShooterObject::update();
}

void PlayerBullet::collsion()
{
    m_bDead = true;
}

EnemyBullet::EnemyBullet(): PlayerBullet()
{

}

std::string EnemyBullet::type()
{
    return "EnemyBullet";
}
