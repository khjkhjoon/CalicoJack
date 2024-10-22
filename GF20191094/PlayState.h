#pragma once
#include"GameState.h"
#include"SDLGameObject.h"
#include"SDL_mixer.h"
#include"SDL_ttf.h"
#include<string.h>
#define _CRT_SECURE_NO_WARNING
class PlayState : public GameState {
public:
	static PlayState* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new PlayState();
		}
		return s_pInstance;
	}
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID()const { return s_playID; }
	static void hit();
    static void stand();
	void sum();
	void draw(int*, int*, int*);
	void result();
	SDL_Surface* text;//surface
	SDL_Surface* moneytext;
	int Money = 1000;
private:
	TTF_Font* font;//�۾� ��Ʈ
	SDL_Color color = { 163,102,68,255 };// �۾� ��
	SDL_Rect srcRect;// �ؽ�Ʈ �������� ������
	SDL_Rect destRect;
	SDL_Rect msrcRect;// �Ӵ� �ؽ�Ʈ �������� ������
	SDL_Rect mdestRect;
	SDL_Texture* texture;//��� texture
	SDL_Texture* moneytexture;
	Mix_Music* music;// ���� ����
	bool start = false;
	int card_jungbok[13] = { 0, };
    int num;// ���� ����
	int x = 20, x_ = 20;
	int y = 372, y_ = 40;
	int p_sum = 0, c_sum = 0;
	static const std::string s_playID;
	PlayState() {}
	static PlayState* s_pInstance;
};