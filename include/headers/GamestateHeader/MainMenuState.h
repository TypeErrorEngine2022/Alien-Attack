#pragma once
#include <vector>
#include <memory>
#include "GameState.h"
#include "MenuState.h"
#include "../EntityHeader/GameObject.h"


class MainMenuState: public MenuState
{
public:
    static std::shared_ptr<MainMenuState> Instance();

    void update() override;
    void render() override;

    bool onEnter() override;

    std::string getStateID() const;

private:
    MainMenuState(){ s_stateID = "MENU";}

    static std::shared_ptr<MainMenuState> s_pInstance;
    
    void setCallbacks(const std::vector<Callback>& callbacks) override;

    //call back function from menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();
};