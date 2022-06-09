#pragma once
#include "../GamestateHeader/GameState.h"
#include <vector>
#include <memory>

template<class T>
class StateMachine
{
public:
    static std::shared_ptr<StateMachine<T>> Instance();

    std::string getCurrentState();

    //add state without removing the previous one
    void pushState(std::shared_ptr<T> pState);

    //remove the previous state before adding another
    void changeState(std::shared_ptr<T> pState);

    //remove current state without adding another
    void popState();

    void update();
    
    void render();

    void clean();

private:
    StateMachine();
    static std::shared_ptr<StateMachine<T>> s_pInstance;

    std::vector<std::shared_ptr<T>> m_states;
    std::shared_ptr<T> newState;
	bool m_bPopStateFlag;
	bool m_bChangeStateFlag;

    void popStatePrivate();
	void changeStatePrivate(std::shared_ptr<T> pState);
};

#include "StateMachine.tpp"