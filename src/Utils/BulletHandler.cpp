#include "../../include/headers/UtilsHeader/BulletHandler.h"
#include "../../include/headers/UtilsHeader/LoaderParams.h"
#include "../../include/headers/UtilsHeader/TextureManager.h"

#include "../../include/headers/Game.h"

std::shared_ptr<BulletHandler> BulletHandler::s_pInstance = nullptr;

std::shared_ptr<BulletHandler> BulletHandler::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = std::shared_ptr<BulletHandler>(new BulletHandler);
    }

    return s_pInstance;
}

BulletHandler::BulletHandler()
{
    TheTextureManager::Instance()->load("src/assets/bullet1.png", "smallbullet", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("src/assets/bullet2.png", "mediumbullet", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("src/assets/bullet3.png", "largebullet", TheGame::Instance()->getRenderer());
}

void BulletHandler::addPlayerBullet(int x, int y, int width, int height, std::string textureID,
                            int numFrames, Vector2D heading)
{
    PlayerBullet pPlayerBullet;
    pPlayerBullet.load(std::make_shared<LoaderParams>(x, y, width, height, textureID, numFrames), heading);
    m_playerBullets.push_front(pPlayerBullet);
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, std::string textureID,
                            int numFrames, Vector2D heading)
{
    EnemyBullet pEnemyBullet;
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
        if (it->getPosition().getX() < 0 || it->getPosition().getX() > TheGame::Instance() -> getGameWidth() ||
            it->getPosition().getY() < 0 || it->getPosition().getY() > TheGame::Instance() -> getGameHeight()  )
        {
            it = m_playerBullets.erase_after(before);
        }
        else
        {
            it->update();

            before = it;
            it++;
        }
    }

    auto before2 = m_enemyBullets.before_begin();
    for (auto it = m_enemyBullets.begin(); it != m_enemyBullets.end(); )
    {
        //exceed the boader
        if (it->getPosition().getX() < 0 || it->getPosition().getX() > TheGame::Instance() -> getGameWidth() ||
            it->getPosition().getY() < 0 || it->getPosition().getY() > TheGame::Instance() -> getGameHeight()  )
        {
            it = m_enemyBullets.erase_after(before2);
        }
        else
        {
            it->update();

            before2 = it;
            it++;
        }
    }

}