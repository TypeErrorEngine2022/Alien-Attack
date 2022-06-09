#include "../../include/headers/Map/ScrollingBackground.h"

ScrollingBackground::ScrollingBackground():
    GameObject()
{

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
    m_currentFrame = 1;
    m_numFrames = pParams -> getNumFrames();
    m_callbackID = pParams -> getCallbackID();
    m_animSpeed = pParams -> getAnimSpeed();
    m_scrollSpeed = pParams -> getAnimSpeed();

    m_scrollSpeed = 1;

    m_srcRect1.x = m_srcRect1.y = 0;
    m_destRect1.x = m_position.getX();
    m_destRect1.y = m_position.getY();

    m_srcRect1.w = m_destRect1.w = m_srcRect1Width = m_destRect1Width = m_width;
    m_srcRect1.h = m_destRect1.h = m_height;

    m_srcRect2.x = m_srcRect2.x = 0;
    m_destRect2.x = m_position.getX() + m_width;
    m_destRect2.y = m_position.getY();

    m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
    m_srcRect2.h = m_destRect2.h = m_height;
}

void ScrollingBackground::draw()
{
    //draw first rect
    SDL_RenderCopyEx(TheGame::Instance() -> getRenderer(), TheTextureManager::Instance() -> getTextureMap()[m_textureID],
                        &m_srcRect1, &m_destRect1, NULL, NULL, SDL_FLIP_NONE);
    
    //draw second rect
    SDL_RenderCopyEx(TheGame::Instance() -> getRenderer(), TheTextureManager::Instance() -> getTextureMap()[m_textureID],
                        &m_srcRect2, &m_destRect2, NULL, NULL, SDL_FLIP_NONE);
}

void ScrollingBackground::update()
{   
    if (count == maxcount)
    {
        //make the first rectangle smaller
        m_srcRect1.x += m_scrollSpeed;
        m_srcRect1.w -= m_scrollSpeed;
        m_destRect1.w -= m_scrollSpeed;

        //make the secon rectangle larger
        m_srcRect2.w += m_scrollSpeed;
        m_destRect2.w += m_srcollSpeed;
        m_destRect2.x -= m_scrollSpeed;

        //reset and start again
        if (m_destRect2.w >= m_width)
        {
            m_srcRect1.x = m_srcRect1.y = 0;
            m_destRect1.x = m_position.getX();
            m_destRect1.y = m_position.getY();

            m_srcRect1.w = m_destRect1.w = m_srcRect1Width = m_destRect1Width = m_width;
            m_srcRect1.h = m_destRect1.h = m_height;

            m_srcRect2.x = m_srcRect2.x = 0;
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