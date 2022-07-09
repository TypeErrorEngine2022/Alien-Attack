#include "../../include/headers/UtilsHeader/CollisionManager.h"
#include "../../include/headers/UtilsHeader/Collision.h"
#include "../../include/headers/UtilsHeader/Vector2D.h"
#include "../../include/headers/UtilsHeader/BulletHandler.h"

#include "../../include/headers/EntityHeader/Bullet.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <forward_list>

void checkPlayerEnemyBulletCollision(std::shared_ptr<Player> pPlayer)
{
    
}

void checkEnemyPlayerBulletCollision(const std::vector<std::shared_ptr<GameObject>>& objects)
{
    for (auto& obj: objects)
    {
        if (obj->type() == static_cast<std::string>("Enemy") && obj->updating())
        {
            SDL_Rect rectE;
            rectE.x = obj->getPosition().getX();
            rectE.y = obj->getPosition().getY();
            rectE.w = obj->getWidth();
            rectE.h = obj->getHeight();

            std::forward_list<PlayerBullet> playerBullets = TheBulletHandler::Instance()->getPlayerBullets();

            for (auto& bullet: playerBullets)
            {
                SDL_Rect rectB;
                rectB.x = bullet.getPosition().getX();
                rectB.y = bullet.getPosition().getY();
                rectB.w = bullet.getWidth();
                rectB.h = bullet.getHeight();

                if (RectRect(rectE, rectB))
                {
                    obj->collision();
                    bullet.collision();
                    std::cout << "Enemy collided with playerbullets\n";
                }
            }
        }
    }
}

void checkPlayerEnemyCollision(std::shared_ptr<Player> pPlayer,
                                         const std::vector<std::shared_ptr<GameObject>>& objects)
{
    SDL_Rect rectP;
    rectP.x = pPlayer->getPosition().getX();
    rectP.y = pPlayer->getPosition().getY();
    rectP.w = pPlayer->getWidth();
    rectP.h = pPlayer->getHeight();

    for (auto& obj: objects)
    {
        if (obj->type() == static_cast<std::string>("Enemy") && obj->updating())
        {
            SDL_Rect rectE;
            rectE.x = obj->getPosition().getX();
            rectE.y = obj->getPosition().getY();
            rectE.w = obj->getWidth();
            rectE.h = obj->getHeight();

            if(RectRect(rectP, rectE))
            {
                pPlayer->collision();
                obj->collision();
                std::cout << "collision detected\n";
            }
        }
    }
}

void checkPlayerTileCollision(std::shared_ptr<Player> pPlayer,
                                         const std::vector<std::shared_ptr<TileLayer>>& collisionLayers)
{
    for (auto& layer: collisionLayers)
    {
        std::shared_ptr<TileLayer> pTileLayer = layer;
        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

        //get this layers position
        Vector2D layerPos = pTileLayer->getPosition();

        int x, y, tileColumn, tileRow, tileid;
        tileid = 0;

        //calculate position on tilemap
        x = layerPos.getX() / pTileLayer->getTileSize();
        y = layerPos.getY() / pTileLayer->getTileSize();

        //if moving forwards or upwards or not moving
        if (pPlayer->getVelocity().getX() >= 0|| pPlayer->getVelocity().getY() >= 0)
        {
            tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / 
                            pTileLayer->getTileSize());
            tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / 
                            pTileLayer->getTileSize());
        }
        //moving backwards or downwards
        else
        {   
            tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
            tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
        }
        
        if (tileColumn >= pTileLayer->getNumTileColumns() || tileRow >= pTileLayer->getNumTileRows())
        {
            continue;
        }
        tileid = tiles[tileRow + y][tileColumn + x];
        
        //if the tile id not blank then collide
        if (tileid != 0)
        {
            pPlayer->collision();
            std::cout << "collided with tiles\n";
        }
    }
}