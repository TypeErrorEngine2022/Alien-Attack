#include "../../include/headers/EntityHeader/Player.h"
#include "../../include/headers/EntityHeader/ShooterObject.h"

#include "../../include/headers/UtilsHeader/LoaderParams.h"
#include "../../include/headers/UtilsHeader/InputHandler.h"

#include "../../include/headers/Game.h"

#include <string>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>

Player::Player() : ShooterObject() 
{

}

void Player::load(const std::shared_ptr<LoaderParams> pParams)
{
    ShooterObject::load(pParams);
}

void Player::draw()
{
    ShooterObject::draw();
}

void Player::update()
{
    //if the level is complete then fly off the screen
    if (TheGame::Instance() -> getLevelComplete())
    {
        if (m_position.getX() >= TheGame::Instance() -> getGameWidth())
        {
            TheGame::Instance() -> setCurrentLevel(TheGame::Instance() -> getCurrentLevel() + 1);
        }
        else
        {
            m_velocity.setY(0);
            m_velocity.setX(3);
            ShooterObject::update();
            handleAnimation();
        }
    }
    else
    {
        //if the player is not doing its death animation then complete it normally
        if (!m_bDying)
        {
            //reset velocity
            m_velocity.setX(0);
            m_velocity.setY(0);

            handleInput();
            ShooterObject::update();

            handleAnimation();
        }
        else //if the player is doing the death animation
        {
            m_currentFrame = static_cast<int>((SDL_GetTicks64() / 100) % m_numFrames);

            //if the death animation is completed
            if (m_dyingCounter == m_dyingTime)
            {
                //resurrect the player
                resurrect();
            }

            m_dyingCounter++;
        }
    }
}

void Player::clean()
{
    std::cout << "cleaning Player\n";
}

void Player::handleInput()
{
    std::shared_ptr<Vector2D> target = TheInputHandler::Instance() -> getMousePosition();

    m_velocity = *target - m_position;
    m_velocity /= 50; //slow down the moving speed, prevent obj from sticking into destination
}

void Player::resurrect()
{
    TheGame::Instance() -> setPlayerLives(TheGame::Instance() -> getPlayerLives() - 1);

    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;

    m_textureID = "player";

    m_currentFrame = 0;
    m_numFrames = 5;
    m_width = 101;
    m_height = 46;

    m_dyingCounter = 0;
    m_invulnerable = true;
}

void Player::handleAnimation()
{
    //if the player is invulnerable, we can flash its alpha to let people know
    if (m_invulnerable)
    {
        //invulnerability is finished, set values back
        if (m_invulnerableCounter == m_invulnerableTime)
        {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        }
        else //flash the alpha on and off
        {
            if (m_alpha == 255)
            {
                m_alpha = 0;
            }
            else
            {
                m_alpha = 255;
            }
        }

        m_invulnerableCounter++;
    }
    
    //if the player is not dead then we can change the angle
    //with the velocity to give the impression of a moving helicopter
    if (!m_bDead)
    {
        if (m_velocity.getX() < 0)
        {
            m_angle = -10.0;
        }
        else if (m_velocity.getX() > 0)
        {
            m_angle = 10.0;
        }
        else
        {
            m_angle = 0.0;
        }
    }

    //our standard animation code - for helicopter propellors
    m_currentFrame = static_cast<int>((SDL_GetTicks64() / 100) % m_numFrames);
}


std::unique_ptr<GameObject> PlayerCreator::createGameObject() const
{
    return std::make_unique<Player>();
}