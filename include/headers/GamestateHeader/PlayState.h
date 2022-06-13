#pragma once
#include "GameState.h"
#include "../EntityHeader/GameObject.h"
#include "../EntityHeader/ShooterObject.h"
#include "../Map/LevelParser.h"
#include <memory>
#include <vector>

class PlayState: public GameState
{
public:
    PlayState(){ s_stateID = "PLAY"; }
    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

    std::shared_ptr<Level> pLevel;
};