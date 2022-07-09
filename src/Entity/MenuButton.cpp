#include "../../include/headers/EntityHeader/MenuButton.h"

#include "../../include/headers/UtilsHeader/LoaderParams.h"
#include "../../include/headers/UtilsHeader/Vector2D.h"
#include "../../include/headers/UtilsHeader/InputHandler.h"
#include "../../include/headers/UtilsHeader/TextureManager.h"

#include "../../include/headers/Game.h"

#include <memory>

MenuButton::MenuButton() : GameObject()
{

}

void MenuButton::load(const std::shared_ptr<LoaderParams> pParams)
{
    m_position = Vector2D(static_cast<double>(pParams -> getX()), static_cast<double>(pParams -> getY()));
    m_velocity = Vector2D(0.0, 0.0);
    m_acceleration = Vector2D(0.0, 0.0);
    m_width = pParams -> getWidth();
    m_height = pParams -> getHeight();
    m_textureID = pParams -> getTextureID();
    m_numFrames = pParams -> getNumFrames();
    m_currentRow = 1;
    //special one
    m_currentFrame = MOUSE_OUT;
    m_numFrames = pParams -> getNumFrames();
    m_callbackID = pParams -> getCallbackID();
    m_animSpeed = pParams -> getAnimSpeed();
}

void MenuButton::setCallback(void(*callback)())
{
    m_callback = callback;
}

void MenuButton::draw()
{
    TheTextureManager::Instance() -> drawFrame(m_textureID, m_position.getX(), m_position.getY(),
                                                m_width, m_height, m_currentRow, m_currentFrame, 
                                                TheGame::Instance() -> getRenderer());
}

void MenuButton::update()
{
    std::shared_ptr<Vector2D> pMousePos = TheInputHandler::Instance() -> getMousePosition();

    if (pMousePos -> getX() > (m_position.getX()) &&
        pMousePos -> getX() < (m_position.getX() + m_width) &&
        pMousePos -> getY() > (m_position.getY()) && 
        pMousePos -> getY() < (m_position.getY() + m_height)) 
    {
        if (TheInputHandler::Instance() -> getMouseButtonState(LEFT) && m_bReleased)
        {
            m_currentFrame = CLICKED;

            TheGame::Instance()->getSoundManager()->playSound("phaser", 1);
            m_callback();

            m_bReleased = false; //prevent from calling the function infinitely when pressing mouse
        }
        else if (!TheInputHandler::Instance() -> getMouseButtonState(LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    
}

void MenuButton::collision()
{

}

std::string MenuButton::type()
{
    return "MenuButton";
}

std::unique_ptr<GameObject> MenuButtonCreator::createGameObject() const
{
    return std::make_unique<MenuButton>();
}

