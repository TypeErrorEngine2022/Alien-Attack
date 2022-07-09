#include "../../include/headers/EntityHeader/Player.h"
#include "../../include/headers/EntityHeader/ShooterObject.h"

#include "../../include/headers/UtilsHeader/LoaderParams.h"
#include "../../include/headers/UtilsHeader/InputHandler.h"
#include "../../include/headers/UtilsHeader/BulletHandler.h"

#include "../../include/headers/GamestateHeader/GameOverState.h"

#include "../../include/headers/Game.h"

#include <string>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>

Player::Player() : ShooterObject(),
    m_invulnerable(false), m_invulnerableTime(60), m_invulnerableCounter(0)
{
    
}

void Player::load(const std::shared_ptr<LoaderParams> pParams)
{
    ShooterObject::load(pParams);

    m_moveSpeed = 3;

    m_bulletFiringSpeed = 13;

    //able to shoot when game starts
    m_bulletCounter = m_bulletFiringSpeed;
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
    
            m_bulletCounter++;
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
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
    {
        m_velocity.setY(-m_moveSpeed);
    }

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && (m_position.getY() + m_height) < TheGame::Instance()->getGameHeight())
    {
        m_velocity.setY(m_moveSpeed);
    }

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth())
    {
        m_velocity.setX(m_moveSpeed);
    }

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
    {
        m_velocity.setX(-m_moveSpeed);
    }

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && m_bulletCounter >= m_bulletFiringSpeed)
    {
        int bulletX = m_position.getX() + 90;
        int bulletY = m_position.getY() + 12;

        TheBulletHandler::Instance()->addPlayerBullet(bulletX, bulletY, 11, 11, "smallbullet", 1, 
                                                        Vector2D(5, 0));
        TheGame::Instance()->getSoundManager()->playSound("foom", 1);

        m_bulletCounter = 0;
    }
}

void Player::collision()
{
    // if the player is not invulnerable then set to dying and change values for death animation tile sheet
    if(!m_invulnerable && !TheGame::Instance()->getLevelComplete())
    {
        m_textureID = "largeexplosion";
        m_currentFrame = 0;
        m_numFrames = 10;
        m_width = 60;
        m_height = 60;
        m_bDying = true;
    }
}

void Player::resurrect()
{
    if (TheGame::Instance()->getPlayerLives() - 1 <= 0)
    {
        TheGame::Instance()->getGameStateMachine()->changeState(GameOverState::Instance());
        return;
    }
    TheGame::Instance() -> setPlayerLives(TheGame::Instance() -> getPlayerLives() - 1);

    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;

    m_textureID = "helicopter";

    m_currentFrame = 0;
    m_numFrames = 5;
    m_width = 128;
    m_height = 55;

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

Vector2D Player::getVelocity() const
{
    return m_velocity;
}

std::unique_ptr<GameObject> PlayerCreator::createGameObject() const
{
    return std::make_unique<Player>();
}