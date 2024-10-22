#pragma once
#include"GameState.h"
//Eenemy -> ���â
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
	SDL_Rect srcRect;//�ؽ�Ʈ �������� ������
	SDL_Rect destRect;
	SDL_Texture* texture = 0;//��� texture
	static void s_WinToMain();
	static void s_restartPlay();
	static const std::string s_gameOverID;

	Enemy() {}
	static Enemy* s_pInstance;
};
