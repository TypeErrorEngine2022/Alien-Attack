#pragma once
#include "Vector2D.h"
#include <memory>
#include <deque>
#include <SDL2/SDL.h>

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance();
    void clean();
    void update();
    void reset();

    bool getMouseButtonState(int buttonNumber);
    std::shared_ptr<Vector2D> getMousePosition();
    
    //handle keyboard events
    void onKeyDown();
    void onKeyUp();
    bool isKeyDown(SDL_Scancode key);

    //handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

private:
    InputHandler();
    ~InputHandler() = default;

    static InputHandler* s_pInstance;
    std::deque<bool> m_mouseButtonStates;
    std::shared_ptr<Vector2D> m_mousePosition;
    const uint8_t* m_keystate;
};

typedef InputHandler TheInputHandler;