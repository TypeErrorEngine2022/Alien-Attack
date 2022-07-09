#include "../../include/headers/EntityHeader/ScrollingBackground.h"

#include "../../include/headers/UtilsHeader/TextureManager.h"
#include "../../include/headers/UtilsHeader/Vector2D.h"

#include "../../include/headers/Game.h"

ScrollingBackground::ScrollingBackground():
    GameObject()
{
    count = 0;
    maxcount = 10;
}

void ScrollingBackground::load(const std::shared_ptr<LoaderParams> pParams)
{
    m_position = Vector2D(static_cast<double>(pParams -> getX()), static_cast<double>(pParams -> getY()));
    m_velocity = Vector2D(0.0, 0.0);
    m_acceleration = Vector2D(0.0, 0.0);
    m_width = pParams -> getWidth();
    m_height = pParams -> getHeight();
    m_textureID = pParams -> getTextureID();
    m_numFrames = pParams -> getNumFrames();
    m_currentRow = 1;
    m_currentFrame = 0;
    m_numFrames = pParams -> getNumFrames();
    m_callbackID = pParams -> getCallbackID();
    m_animSpeed = pParams -> getAnimSpeed();

    m_scrollSpeed = 1;

    m_srcRect1.x = m_srcRect1.y = 0;
    m_destRect1.x = m_position.getX();
    m_destRect1.y = m_position.getY();

    m_srcRect1.w = m_destRect1.w = m_srcRect1Width = m_destRect1Width = m_width;
    m_srcRect1.h = m_destRect1.h = m_height;

    m_srcRect2.x = m_srcRect2.y = 0;
    //so two rect are adjacent
    //eg. rect1.x = 0, rect1.w = 640 => rect2.x = 640, near rect1
    m_destRect2.x = m_position.getX() + m_width;
    m_destRect2.y = m_position.getY();

    m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
    m_srcRect2.h = m_destRect2.h = m_height;
}

void ScrollingBackground::draw()
{
    //draw first rect
    SDL_RenderCopyEx(TheGame::Instance() -> getRenderer(), TheTextureManager::Instance() -> getTextureMap()[m_textureID],
                        &m_srcRect1, &m_destRect1, 0, nullptr, SDL_FLIP_NONE);
    
    //draw second rect
    SDL_RenderCopyEx(TheGame::Instance() -> getRenderer(), TheTextureManager::Instance() -> getTextureMap()[m_textureID],
                        &m_srcRect2, &m_destRect2, 0, nullptr, SDL_FLIP_NONE);
}

void ScrollingBackground::update()
{   
    if (count == maxcount)
    {
        //make the first rectangle smaller
        //decrease the width => contract the rect
        m_srcRect1.x += m_scrollSpeed;
        m_srcRect1.w -= m_scrollSpeed;
        m_destRect1.w -= m_scrollSpeed;

        //make the second rectangle larger
        //increase the width => expand the rect
        m_srcRect2.w += m_scrollSpeed;
        m_destRect2.w += m_scrollSpeed;
        m_destRect2.x -= m_scrollSpeed;

        //reset and start again
        if (m_destRect2.w >= m_width)
        {
            m_srcRect1.x = m_srcRect1.y = 0;
            m_destRect1.x = m_position.getX();
            m_destRect1.y = m_position.getY();

            m_srcRect1.w = m_destRect1.w = m_srcRect1Width = m_destRect1Width = m_width;
            m_srcRect1.h = m_destRect1.h = m_height;

            m_srcRect2.x = m_srcRect2.y = 0;
            m_destRect2.x = m_position.getX() + m_width;
            m_destRect2.y = m_position.getY();

            m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
            m_srcRect2.h = m_destRect2.h = m_height;
        }

        count = 0;
    }

    count++;
}

void ScrollingBackground::clean()
{

}

std::string ScrollingBackground::type()
{
    return "ScrollingBackground";
}

void ScrollingBackground::collision()
{
    
}

std::unique_ptr<GameObject> ScrollingBackgroundCreator::createGameObject() const
{
    return std::make_unique<ScrollingBackground>();
}