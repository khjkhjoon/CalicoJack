#include"Game.h"
#include<iostream>
#include"GameStateMachine.h"
#include"Enemy.h"
#include"MenuButton.h"
#include"MenuState.h"
#include"PlayState.h"
#include"AnimatedGraphic.h"
#include"SDL_ttf.h"
#include"GameOverState.h"
const std::string Enemy::s_gameOverID = "GameOVER";
Enemy* Enemy::s_pInstance = NULL;
void Enemy::s_WinToMain() {
	TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
}
void Enemy::s_restartPlay() {
	TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
}
void Enemy::update() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}
void Enemy::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
bool Enemy::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/card_/money.png", "coin", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/menubutton.png", "mainbutton", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/rebutton.png", "restartbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* button1 = new MenuButton(new LoaderParams(305, 200, 159, 90, "mainbutton"), s_WinToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(305, 300, 159, 90, "restartbutton"), s_restartPlay);
	GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(500, 120, 64, 64, "coin"), 4);
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = 300;
	srcRect.h = destRect.h = 100;
	destRect.x = 270;
	destRect.y = 100;
	texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), text);
	SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(gameOverText);
	std::cout << "entering Enemy\n";
	return true;
}
bool Enemy::onExit() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
	TheTextureManager::Instance()->clearFromTextureMap("coin");
	std::cout << "exiting Enemy\n";
	return true;
}