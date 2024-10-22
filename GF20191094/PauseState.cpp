#include "Game.h"
#include"MenuState.h"
#include"MenuButton.h"
#include<iostream>
#include"GameStateMachine.h"
#include"PauseState.h"
const std::string PauseState::s_pauseID = "PAUSE";
PauseState* PauseState::s_pInstance = NULL;
void PauseState::update() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}
void PauseState::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}
void PauseState::s_pauseToMain() {
	TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
}
void PauseState::s_resumePlay() {
	TheGame::Instance()->getStateMachine()->popState();
}
bool PauseState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/card_/rebutton.png", "resumebutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/card_/menubutton.png", "mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* button1 = new MenuButton(new LoaderParams(100, 80, 159, 90, "mainbutton"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 159, 90, "resumebutton"), s_resumePlay);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering PauseState\n";
	return true;

}
bool PauseState::onExit() { 
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("resumebutton");
	std::cout << "exiting PauseState\n";
	return true; }