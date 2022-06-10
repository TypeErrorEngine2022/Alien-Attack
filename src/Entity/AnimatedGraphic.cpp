#include "../../include/headers/EntityHeader/AnimatedGraphic.h"

#include "../../include/headers/UtilsHeader/TextureManager.h"

#include "../../include/headers/Game.h"

AnimatedGraphic::AnimatedGraphic() : GameObject()
{

}

void AnimatedGraphic::load(const std::shared_ptr<LoaderParams> pParams)
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

void AnimatedGraphic::draw()
{
    TheTextureManager::Instance() -> drawFrame(m_textureID, m_position.getX(), m_position.getY(),
                                                m_width, m_height, m_currentRow, m_currentFrame, 
                                                TheGame::Instance() -> getRenderer());
}


void AnimatedGraphic::update()
{
    m_currentFrame = static_cast<int>((SDL_GetTicks64() / (1000 / m_animSpeed)) % m_numFrames);

}

void AnimatedGraphic::clean()
{

}

void AnimatedGraphic::collision()
{
    
}

std::string AnimatedGraphic::type()
{
    return "AnimatedGraphic";
}

std::unique_ptr<GameObject> AnimatedGraphicCreator::createGameObject() const
{
    return std::make_unique<AnimatedGraphic>();
}