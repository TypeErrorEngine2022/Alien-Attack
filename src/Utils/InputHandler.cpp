#include "../../include/headers/UtilsHeader/InputHandler.h"
#include "../../include/headers/Game.h"
#include "../../include/headers/UtilsHeader/Vector2D.h"
#include <memory>
#include <iostream>
#include <SDL2/SDL.h>

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler* InputHandler::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = new InputHandler;
        return s_pInstance;
    }
    return s_pInstance;
}

InputHandler::InputHandler()
{
    for (int i = 0; i < 3; ++i)
    {
        m_mouseButtonStates.push_back(false);
    }
    
    m_mousePosition = std::make_shared<Vector2D>();
    m_keystate = SDL_GetKeyboardState(NULL); 
}

void InputHandler::clean()
{
    std::cout << "delete inputhandler\n";
    delete s_pInstance;
    s_pInstance = nullptr;

    m_keystate = nullptr; // do not free the content of it, see SDL_GetKeyboardState;
}

void InputHandler::reset()
{
    for (int i = 0; i < 3; i++)
    {
        m_mouseButtonStates[i] = false;
    }
}

std::shared_ptr<Vector2D> InputHandler::getMousePosition()
{
    return m_mousePosition;
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    switch (event.button.button)
    {
    case SDL_BUTTON_LEFT:
        m_mouseButtonStates[LEFT] = false;
        break;
    
    case SDL_BUTTON_MIDDLE:
        m_mouseButtonStates[MIDDLE] = false;
        break;

    case SDL_BUTTON_RIGHT:
        m_mouseButtonStates[RIGHT] = false;
        break;

    default:
        break;
    }
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    switch (event.button.button)
    {
    case SDL_BUTTON_LEFT:
        m_mouseButtonStates[LEFT] = true;
        break;
    
    case SDL_BUTTON_MIDDLE:
        m_mouseButtonStates[MIDDLE] = true;
        break;

    case SDL_BUTTON_RIGHT:
        m_mouseButtonStates[RIGHT] = true;
        break;

    default:
        break;
    }
}

void InputHandler::onMouseMove(SDL_Event& event)
{
    m_mousePosition -> setX(event.motion.x);
    m_mousePosition -> setY(event.motion.y);
}

void InputHandler::onKeyDown()
{
    //update pressed key
    m_keystate = SDL_GetKeyboardState(NULL);
}

void InputHandler::onKeyUp()
{
    m_keystate = SDL_GetKeyboardState(NULL);
}

bool InputHandler::isKeyDown(SDL_Scancode key) //scancode is enum of key in keyboard
{
    if (m_keystate != nullptr)
    {
        if (m_keystate[key]) // m_keystate will change continuously
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

void InputHandler::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            TheGame::Instance() -> quit();
            break;
        
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;

        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
        
        case SDL_KEYDOWN:
            onKeyDown();
            break;

        case SDL_KEYUP:
            onKeyUp();
            break;

        default:
            break;
        }
    
    }
}



