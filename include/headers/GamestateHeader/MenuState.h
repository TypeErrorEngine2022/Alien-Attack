#pragma once
#include "GameState.h"
#include <vector>

class MenuState: public GameState
{
protected:
    //set void(*Callback)() be Callback
    typedef void(*Callback)();
    std::vector<Callback> m_callbacks;
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
};