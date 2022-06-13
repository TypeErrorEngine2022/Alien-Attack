#include "../../include/headers/EntityHeader/GameObject.h"

//set to default
GameObject::GameObject():
    m_position(0.0, 0.0), m_velocity(0.0, 0.0), m_acceleration(0.0, 0.0),
    m_width(0), m_height(0), m_currentRow(0), m_currentFrame(0),
    m_bUpdating(false), m_bDead(false), m_bDying(false), m_angle(0), m_alpha(255)
{

}

Vector2D GameObject::getPosition() const
{
    return m_position;
}

int GameObject::getWidth() const
{
    return m_width;
}

int GameObject::getHeight() const
{
    return m_height;
}

int GameObject::getCallbackID() const
{
    return m_callbackID;
}


/**
 * @brief Move the gameobject leftwards, try to go into the scence
 * 
 * @param scrollSpeed additional velocity for the movement
 */
void GameObject::scroll(double scrollSpeed)
{
    m_position.setX(m_position.getX() - scrollSpeed);
}

bool GameObject::updating()
{
    return m_bUpdating;
}

void GameObject::setUpdating(bool updating)
{
    m_bUpdating = updating;
}

bool GameObject::dead()
{
    return m_bDead;
}

bool GameObject::dying()
{
    return m_bDying;
}
