#pragma once
#include "StateMachine.h"
#include <string>
#include <iostream>
#include <memory>

template <typename T>
std::shared_ptr<StateMachine<T>> StateMachine<T>::s_pInstance = nullptr;

template <typename T>
StateMachine<T>::StateMachine():
    m_bPopStateFlag(false), m_bChangeStateFlag(false)
{}

template <typename T>
std::shared_ptr<StateMachine<T>> StateMachine<T>::Instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = std::shared_ptr<StateMachine<T>>(new StateMachine<T>);
        return s_pInstance;
    }
    return s_pInstance;
}

template <typename T>
std::string StateMachine<T>::getCurrentState()
{
    return m_states.back() -> getStateID();
}

template <typename T>
void StateMachine<T>::pushState(std::shared_ptr<T> pState)
{
	for(auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if(((*it)->getStateID() == pState->getStateID()) && ((*it)->onExit()))
		{
			m_states.erase(it);
			break;
		}
	}

    m_states.push_back(pState);

    if (!m_states.back() -> onEnter())
    {
        std::cout << "Fail to push_back State\n";
    }
}

template <typename T>
void StateMachine<T>::popStatePrivate()
{
    if(!m_states.empty())
	{
		if(m_states.back()->onExit())
		{
			m_states.pop_back();
		}
	}
}

template <typename T>
void StateMachine<T>::popState()
{
    m_bPopStateFlag = true;
}

template <typename T>
void StateMachine<T>::changeStatePrivate(std::shared_ptr<T> pState)
{
    if(!m_states.empty())
	{
		if(m_states.back() -> getStateID() == pState -> getStateID())
		{
			return; // do nothing
		}

		if(m_states.back() -> onExit())
		{
			m_states.pop_back();
		}

		// We check if the State exists in the StateMachine, if it exists
		// we eliminate them to free memory and an unneeded State
		for(auto it = m_states.begin(); it != m_states.end(); ++it)
		{
			if(((*it)->getStateID() == pState->getStateID()) && ((*it)->onExit()))
			{
				std::cout << "Detected unneeded state: " << pState -> getStateID() << "\n";
				m_states.erase(it);
				break;
			}
		}
	}
	
	m_states.push_back(pState);
	
	// initialise it
	m_states.back() -> onEnter();
}

template <typename T>
void StateMachine<T>::changeState(std::shared_ptr<T> pState)
{
	std::cout << "change state flag activated\n";
    m_bChangeStateFlag = true;
    newState = pState;
}

template <typename T>
void StateMachine<T>::update()
{
    if(!m_states.empty())
	{
		m_states.back()->update();
	}
	
	if(m_bChangeStateFlag)
	{
		std::cout << "Going to change state\n";
		changeStatePrivate(newState);
		m_bChangeStateFlag = false;
	}
	else if(m_bPopStateFlag)
	{
		std::cout << "Going to pop state\n";
		popStatePrivate();
		m_bPopStateFlag = false;
	}
}

template <typename T>
void StateMachine<T>::render()
{
    if (!m_states.empty())
    {
        m_states.back() -> render();
    }
}

template <typename T>
void StateMachine<T>::clean()
{
	while (!m_states.empty())
	{
		if (m_states.back() -> onExit())
		{
			m_states.pop_back();
		}
	}
}