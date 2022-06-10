#pragma once
#include <memory>
#include <string>
#include <forward_list>

#include "../UtilsHeader/Vector2D.h"
#include "../EntityHeader/Bullet.h"

enum bullet_type
{
    smallBullet = 0,
    mediumBullet = 1,
    largeBullet = 2
};

class BulletHandler
{
public:
    static std::shared_ptr<BulletHandler> Instance();
    BulletHandler(const BulletHandler& rhs) = delete;
    BulletHandler(BulletHandler&& rhs) = delete;

    void addPlayerBullet(int x, int y, int width, int height, std::string textureID,
                            int numFrames, Vector2D heading);
    void addEnemyBullet(int x, int y, int width, int height, std::string textureID,
                            int numFrames, Vector2D heading);

    void draw();

    void update();

private:
    BulletHandler();
    
    static std::shared_ptr<BulletHandler> s_pInstance;

    std::forward_list<PlayerBullet> m_playerBullets;
    std::forward_list<EnemyBullet> m_enemyBullets;
};

typedef BulletHandler TheBulletHandler;