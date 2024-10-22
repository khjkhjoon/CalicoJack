#pragma once
#include"GameState.h"
//Eenemy -> 결과창
class GameObject;
class Enemy :public GameState {
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID()const { return s_gameOverID; }
	static Enemy* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Enemy();
		}
		return s_pInstance;
	}
	SDL_Surface* text = 0;//surface
private:
	SDL_Rect srcRect;//텍스트 원본상자 대상상자
	SDL_Rect destRect;
	SDL_Texture* texture = 0;//출력 texture
	static void s_WinToMain();
	static void s_restartPlay();
	static const std::string s_gameOverID;

	Enemy() {}
	static Enemy* s_pInstance;
};
