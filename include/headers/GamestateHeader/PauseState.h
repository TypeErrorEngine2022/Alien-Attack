#pragma once
#include "MenuState.h"
#include "../EntityHeader/GameObject.h"
#include <memory>
#include <string>
#include <vector>

class PauseState: public MenuState
{
public:
    static std::shared_ptr<PauseState> Instance();

    void update() override;
    void render() override;

    bool onEnter() override;

    std::string getStateID() const override;

private:
    PauseState(){ s_stateID = "PAUSE"; }

    static std::shared_ptr<PauseState> s_pInstance;

    static void s_pauseToMain();
    static void s_resumePlay();
    void setCallbacks(const std::vector<Callback>& callbacks) override;
};

