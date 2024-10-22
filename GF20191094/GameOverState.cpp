#include"Game.h"
#include<iostream>
#include"GameStateMachine.h"
#include"GameOverState.h"
#include"MenuButton.h"
#include"MenuState.h"
#include"PlayState.h"
#include"AnimatedGraphic.h"
const std::string GameOverState::s_gameOverID = "GameOVER";
GameOverState* GameOverState::s_pInstance = NULL;
void GameOverState::up() {
	if (GameOverState::Instance()->betamount < 5000)
		GameOverState::Instance()->betamount += 100;
}
void GameOverState::down() {
	if (GameOverState::Instance()->betamount > 100)
		GameOverState::Instance()->betamount -= 100;
}
void GameOverState::betting() {
	if (GameOverState::Instance()->betamount <= PlayState::Instance()->Money) {
		TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
		PlayState::Instance()->Money -= GameOverState::Instance()->betamount;
	}
}
void GameOverState::update() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
	sum();
}
void GameOverState::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
	if (start) {
		SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
		SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), mtexture, &msrcRect, &mdestRect, 0, 0, SDL_FLIP_NONE);
	}
}
bool GameOverState::onEnter() {
	if (PlayState::Instance()->Money == 0) {
		TheGame::Instance()->m_bRunning = false;//돈이 0원일 경우 게임 종료
	}
	if (!TheTextureManager::Instance()->load("assets/card_/upbutton.png", "UB", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/downbutton.png", "DB", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/betbutton.png", "BB", TheGame::Instance()->getRenderer())) {
		return false;
	}
	betamount = 100;
	font = TTF_OpenFont("assets/DOSMyungjo.ttf", 100);
	GameObject* button1 = new MenuButton(new LoaderParams(400, 170, 53, 30, "UB"), up);
	GameObject* button2 = new MenuButton(new LoaderParams(400, 233, 53, 30, "DB"), down);
	GameObject* button3 = new MenuButton(new LoaderParams(400, 201, 53, 30, "BB"), betting);
	
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);
	msrcRect.x = srcRect.x = 0;
	msrcRect.y = srcRect.y = 0;
	srcRect.w = destRect.w = 80;
	srcRect.h = destRect.h = 30;
	msrcRect.w = mdestRect.w = 100;
	msrcRect.h = mdestRect.h = 30;
	destRect.x = 300;
	destRect.y = 201;
	mdestRect.x = 600;
	mdestRect.y = 210;
	std::cout << "entering GameOverState\n";
	return true;
}
bool GameOverState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("UB");
	TheTextureManager::Instance()->clearFromTextureMap("DB");	
	TheTextureManager::Instance()->clearFromTextureMap("BB");
	SDL_FreeSurface(text);//surface 해제
	SDL_DestroyTexture(texture);
	std::cout << "exiting GameOverState\n";
	return true;
}
void GameOverState::sum() {
	char s[5], s1[256], s2[256];
	sprintf_s(s, "%d", betamount);//p_sum을 문자열로 변환
	text = TTF_RenderText_Solid(font, s, color);
	texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), text);

	SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
	strcpy_s(s1, 256, "Money=");
	sprintf_s(s2, "%d", PlayState::Instance()->Money);
	strcat_s(s1, sizeof(s1), s2);
	mtext = TTF_RenderText_Solid(font, s1, color);
	mtexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), mtext);
	SDL_QueryTexture(mtexture, NULL, NULL, &msrcRect.w, &msrcRect.h);
	start = true;
}