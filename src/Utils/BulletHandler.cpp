#include "../../include/headers/UtilsHeader/BulletHandler.h"
#include "../../include/headers/UtilsHeader/LoaderParams.h"

std::shared_ptr<BulletHandler> BulletHandler::s_pInstance = nullptr;

std::shared_ptr<BulletHandler> BulletHandler::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = std::make_shared<BulletHandler>(new BulletHandler);
    }

    return s_pInstance;
}

void BulletHandler::addPlayerBullet(int x, int y, int width, int height, std::string textureID,
                            int numFrames, Vector2D heading)
{
    PlayerBullet pPlayerBullet();
    pPlayerBullet.load(std::make_shared<LoaderParams>(x, y, width, height, textureID, numFrames), heading);
    m_playerBullets.push_front(pPlayerBullet);
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, std::string textureID,
                            int numFrames, Vector2D heading)
{
    EnemyBullet pEnemyBullet();
    pEnemyBullet.load(std::make_shared<LoaderParams>(x, y, width, height, textureID, numFrames), heading);
    m_enemyBullets.push_front(pEnemyBullet);
}

void BulletHandler::draw()
{
    for (auto& bullet: m_playerBullets)
    {
        bullet.draw();
    }

    for (auto& bullet: m_enemyBullets)
    {
        bullet.draw();
    }
}

void BulletHandler::update()
{
    auto before = m_playerBullets.before_begin();

    for (auto it = m_playerBullets.begin(); it != m_playerBullets.end(); )
    {
        //excedd the boader
        if (it.getPosition().getX() < 0 || it.getPosition().getX() > TheGame::Instance() -> getGameWidth() ||
            it.getPosition().getY() < 0 || it.getPosition().getY() > TheGame::Instance() -> getGameHeight()  )
        {
            it = m_playerBullets.erase_after(before);
        }
        else
        {
            it.update();

            before = it;
            it++;
        }
    }

    before = m_enemyBullets.before_begin();
    for (auto it = m_enemyBullets.begin(); it != m_enemyBullets.end(); )
    {
        //excedd the boader
        if (it.getPosition().getX() < 0 || it.getPosition().getX() > TheGame::Instance() -> getGameWidth() ||
            it.getPosition().getY() < 0 || it.getPosition().getY() > TheGame::Instance() -> getGameHeight()  )
        {
            it = m_enemyBullets.erase_after(before);
        }
        else
        {
            it.update();

            before = it;
            it++;
        }
    }

}