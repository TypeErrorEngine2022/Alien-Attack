#pragma once
#include "GameObject.h"
#include "../UtilsHeader/LoaderParams.h"
#include "../UtilsHeader/BaseCreator.h"
#include <memory>
#include <string>

class MenuButton: public GameObject
{
public:
    MenuButton();

    void load(const std::shared_ptr<LoaderParams> pParams) override;

    void setCallback(void(*callback)());

    void draw() override;
    void update() override;
    void clean() override;

    void collsion() override;

    std::string type() override;

private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    //m_callback is name for void(*)() function pointer
    void (*m_callback)();
    bool m_bReleased;
};

class MenuButtonCreator: public BaseCreator
{
public:
    std::unique_ptr<GameObject> createGameObject() const override;
};