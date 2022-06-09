#pragma once
#include "../EntityHeader/GameObject.h"
#include "MenuState.h"
#include <vector>
#include <string>
#include <memory>

class GameOverState: public MenuState
{
public:
    static std::shared_ptr<GameOverState> Instance();

    void update() override;
    void render() override;

    bool onEnter() override;

    std::string getStateID() const;

private:
    GameOverState(){ s_stateID = "GAMEOVER"; }
    static std::shared_ptr<GameOverState> s_pInstance;
    
    static void s_restartPlay();
    static void s_gameOverToMain();
    void setCallbacks(const std::vector<Callback>& callbacks) override;
};