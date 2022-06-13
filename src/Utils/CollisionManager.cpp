#include "../../include/headers/UtilsHeader/CollisionManager.h"
#include "../../include/headers/UtilsHeader/Collision.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

void checkPlayerEnemyBulletCollision(std::shared_ptr<Player> pPlayer)
{
    
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

}