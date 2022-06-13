#pragma once
#include "../EntityHeader/Player.h"
#include "../EntityHeader/GameObject.h"

#include "../Map/TileSet.h"
#include "../Map/TileLayer.h"

#include <memory>
#include <vector>

void checkPlayerEnemyBulletCollision(std::shared_ptr<Player> pPlayer);

void checkPlayerEnemyCollision(std::shared_ptr<Player> pPlayer,
                                         const std::vector<std::shared_ptr<GameObject>>& objects);

void checkPlayerTileCollision(std::shared_ptr<Player> pPlayer,
                                         const std::vector<std::shared_ptr<TileLayer>>& collisionLayers);