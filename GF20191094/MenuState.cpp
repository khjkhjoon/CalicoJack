#include "MenuState.h"
#include<iostream>
#include "GameObject.h"
#include"TextureManager.h"
#include"Game.h"
#include"PlayState.h"
#include"GameOverState.h"
#include"MenuButton.h"
#include "GameStateMachine.h"
MenuState* MenuState::s_pInstance = NULL;
const std::string MenuState::s_menuID = "MENU";
void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}
void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}
bool MenuState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/card_/playbutton.png", "playbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/card_/exitbutton.png", "exitbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* button1 = new MenuButton(new LoaderParams(305, 100, 159, 90, "playbutton"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(305, 300, 159, 90, "exitbutton"), s_exitFromMenu);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
	std::cout << "exiting MenuState\n";
	return true;
}
void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
}
void MenuState::s_exitFromMenu()
{
	std::cout << "Exit button clicked\n";
	TheGame::Instance()->quit();
}