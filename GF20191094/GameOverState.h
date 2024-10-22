#pragma once
#include"GameState.h"
#include"SDL_ttf.h"
class GameObject;
class GameOverState :public GameState {
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID()const { return s_gameOverID; }
	static GameOverState* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new GameOverState();
		}
		return s_pInstance;
	}
	static void up();
	static void down();
	static void betting();
	int betamount;
private:
	void sum();
	bool start = false;
	static const std::string s_gameOverID;
	
	TTF_Font* font;//�۾� ��Ʈ
	SDL_Color color = { 255,255,255,255 };// �۾� ��
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Rect msrcRect;
	SDL_Rect mdestRect;
    SDL_Surface* text;//surface
	SDL_Texture* texture;//��� texture
	SDL_Surface* mtext;//�� surface
	SDL_Texture* mtexture;//����� texture

	GameOverState(){}
	static GameOverState* s_pInstance;
};
