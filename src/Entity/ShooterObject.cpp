#include "../../include/headers/EntityHeader/ShooterObject.h"
#include "../../include/headers/UtilsHeader/LoaderParams.h"
#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/Game.h"
#include "../../include/headers/EntityHeader/GameObject.h"
#include "../../include/headers/UtilsHeader/Vector2D.h"
#include <memory>
#include <iostream>

ShooterObject::ShooterObject(): GameObject()
{
    
}

void ShooterObject::load(const std::shared_ptr<LoaderParams> pParams)
{
    m_position = Vector2D(static_cast<double>(pParams -> getX()), static_cast<double>(pParams -> getY()));
    m_velocity = Vector2D(0.0, 0.0);
    m_acceleration = Vector2D(0.0, 0.0);
    m_width = pParams -> getWidth();
    m_height = pParams -> getHeight();
    m_textureID = pParams -> getTextureID();
    m_numFrames = pParams -> getNumFrames();
    m_currentRow = 1;
    m_currentFrame = 1;
    m_numFrames = pParams -> getNumFrames();
    m_callbackID = pParams -> getCallbackID();
    m_animSpeed = pParams -> getAnimSpeed();
}

void ShooterObject::draw()
{
    if (m_velocity.getX() > 0) // rightwards is the opposite side of helicopter
    {
        TextureManager::Instance() -> drawFrame(m_textureID, static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), 
                                                m_width, m_height, m_currentRow, m_currentFrame, 
                                                TheGame::Instance() -> getRenderer(), 0, 0, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        TextureManager::Instance() -> drawFrame(m_textureID, static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), 
                                            m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance() -> getRenderer());
    }
}

void ShooterObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void ShooterObject::clean()
{}

void ShooterObject::collision()
{}

std::string ShooterObject::type()
{
    return "ShooterObject";
}

bool ShooterObject::dead()
{
    return m_bDead;
}

bool ShooterObject::dying()
{
    return m_bDying;
}

void ShooterObject::doDyingAnimation()
{
    //keep scrolling with the map
    scroll(TheGame::Instance() -> getScrollSpeed());

    m_currentFrame = static_cast<int>( (SDL_GetTicks64() / (1000 / 3)) % m_numFrames);

    if (m_dyingCounter == m_dyingTime)
    {
        m_bDead = true;
    }
    m_dyingCounter++; //simple counter, fine with fixed frame rate
}