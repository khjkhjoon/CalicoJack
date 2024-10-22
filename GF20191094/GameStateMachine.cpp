#include "GameStateMachine.h"
#include"PlayState.h"
#include"PauseState.h"
void GameStateMachine::popState()
{
	if (m_currentState != PauseState::Instance())
	changeState(m_prevState);
	else {
		m_currentState->onExit();
		m_currentState = m_prevState;
	}
}
void GameStateMachine::changeState(GameState* pState) {
	if (pState != NULL) {
		if (m_currentState != NULL)
		{
			m_prevState = m_currentState;
			if (pState != PauseState::Instance())
			m_currentState->onExit();
		}
     m_currentState = pState;
	 m_currentState->onEnter();
	}
}
void GameStateMachine::update()
{
	if (m_currentState != NULL)
		m_currentState->update();
}
void GameStateMachine::render() {
	if (m_currentState != NULL)
		m_currentState->render();
}