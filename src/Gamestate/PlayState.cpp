#include "../../include/headers/Game.h"
#include "../../include/headers/EntityHeader/GameObject.h"

#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/UtilsHeader/InputHandler.h"
#include "../../include/headers/UtilsHeader/StateParser.h"
#include "../../include/headers/UtilsHeader/CollisionManager.h"

#include "../../include/headers/Map/LevelParser.h"

#include "../../include/headers/GamestateHeader/PauseState.h"
#include "../../include/headers/GamestateHeader/PlayState.h"
#include "../../include/headers/GamestateHeader/GameOverState.h"

#include "../../include/headers/EntityHeader/Player.h"
#include "../../include/headers/EntityHeader/Enemy.h"

#include <string>
#include <iostream>
#include <memory>
#include <vector>


std::string PlayState::getStateID() const
{
    return s_stateID;
}

void PlayState::update()
{
    if (TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance() -> getGameStateMachine() -> pushState(PauseState::Instance());
    }

    pLevel -> update();
}

void PlayState::render()
{
    pLevel -> render();
}

bool PlayState::onEnter()
{
    std::cout << "entering PlayState\n";

    LevelParser levelParser;
    pLevel = levelParser.parseLevel("C:/Users/jacky/Desktop/sdl_game/src/assets/Map/map1.tmx");

    TheGame::Instance()->getSoundManager()->playMusic("playbgm", -1);

    return true;
}

bool PlayState::onExit()
{
    pLevel->clean();
    TheInputHandler::Instance() -> reset();
    std::cout << "exiting " << s_stateID << '\n';
    return true;
}

