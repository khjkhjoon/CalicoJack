#include "PlayState.h"
#include "GameObject.h"
#include"GameOverState.h"
#include"PauseState.h"
#include"GameStateMachine.h"
#include"Game.h"
#include"MenuButton.h"
#include<time.h>
#include<iostream>
#include<stdlib.h>
#include"Enemy.h"
#include"SDL_ttf.h"
const std::string PlayState::s_playID = "PLAY";
#define _CRT_SECURE_NO_WARNING
PlayState* PlayState::s_pInstance = NULL;
void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->getStateMachine()->changeState(PauseState::Instance());
	}
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
	if (p_sum > 21) {
		Enemy::Instance()->text = TTF_RenderText_Solid(font, "Lose ", color);// Lose ���� ����
		TheGame::Instance()->getStateMachine()->changeState(Enemy::Instance());
	}
	sum();
}
void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
	if (start) {
		SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
		SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), moneytexture, &msrcRect, &mdestRect, 0, 0, SDL_FLIP_NONE);
	}
	
}
bool PlayState::onEnter()
{
	
		Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);//���̺귯�� �ʱ�ȭ
		if (!TheTextureManager::Instance()->load("assets/card_/card1.png", "card1", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card2.png", "card2", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card3.png", "card3", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card4.png", "card4", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card5.png", "card5", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card6.png", "card6", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card7.png", "card7", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card8.png", "card8", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card9.png", "card9", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card10.png", "card10", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card11.png", "card11", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card12.png", "card12", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/hitbutton.png", "hit", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets/card_/card13.png", "card13", TheGame::Instance()->getRenderer()) || !TheTextureManager::Instance()->load("assets//card_/stdbutton.png", "stand", TheGame::Instance()->getRenderer())) {
			return false;
		}
		srand((unsigned int)time(NULL));
		music = Mix_LoadMUS("assets/Catcher.mp3");//����� �ε�
		GameObject* button1 = new MenuButton(new LoaderParams(330, 210, 53, 30, "hit"), hit);
		GameObject* button2 = new MenuButton(new LoaderParams(410, 210, 53, 30, "stand"), stand);	
		font = TTF_OpenFont("assets/DOSMyungjo.ttf",100);// �۲ð� ũ�� �ε�
		//color = { 255,255,255,255 };// �۾� ��
		m_gameObjects.push_back(button1);
		m_gameObjects.push_back(button2);
		Mix_VolumeMusic(20); //���� ����
		Mix_PlayMusic(music, -1);//����� ���� ���
		for (int i = 0; i < 4; i++) {//ī�� �̴� �Լ�
			if (i < 2)
				draw(&x, &y, &p_sum);//�÷��̾� ī�� 2��
			else
				draw(&x_, &y_, &c_sum);//��ǻ�� ī�� 2��
		}
		msrcRect.x = srcRect.x = 0;//�ؽ�Ʈ�� �������ڿ� ������
		msrcRect.y = srcRect.y = 0;
		msrcRect.w = mdestRect.w = srcRect.w = destRect.w = 100;
		msrcRect.h = mdestRect.h = srcRect.h = destRect.h = 30;
		destRect.x = 10;
		destRect.y = 300;
		mdestRect.x = 600;
		mdestRect.y = 210;
		std::cout << "entering PlayState\n";
	   return true;
}
bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()
		->clearFromTextureMap("card1");
	TheTextureManager::Instance()
		->clearFromTextureMap("card2");
	TheTextureManager::Instance()
		->clearFromTextureMap("card3");
	TheTextureManager::Instance()
		->clearFromTextureMap("card4");
	TheTextureManager::Instance()
		->clearFromTextureMap("card5");
	TheTextureManager::Instance()
		->clearFromTextureMap("card6");
	TheTextureManager::Instance()
		->clearFromTextureMap("card7");
	TheTextureManager::Instance()
		->clearFromTextureMap("card8");
	TheTextureManager::Instance()
		->clearFromTextureMap("card9");
	TheTextureManager::Instance()
		->clearFromTextureMap("card10");
	TheTextureManager::Instance()
		->clearFromTextureMap("card11");
	TheTextureManager::Instance()
		->clearFromTextureMap("card12");
	TheTextureManager::Instance()
		->clearFromTextureMap("card13");
	TheTextureManager::Instance()
		->clearFromTextureMap("hit");
	TheTextureManager::Instance()
		->clearFromTextureMap("stand");
	Mix_FreeMusic(music);//����� ����
	Mix_CloseAudio();//��� ���� ����
	SDL_FreeSurface(text);//surface ����
	SDL_DestroyTexture(texture);//�ؽ��� ����
	SDL_FreeSurface(moneytext);//surface ����
	SDL_DestroyTexture(moneytexture);//�ؽ��� ����
	std::cout << "exiting PlayState\n";
	
	card_jungbok[12] = { 0, };//������ �ʱ�ȭ
	x = 20, x_ = 20;
	y = 372, y_ = 40;
	p_sum = 0, c_sum = 0;
	return true;
}
void PlayState::hit() { 
	PlayState::Instance()->draw(&PlayState::Instance()->x, &PlayState::Instance()->y, &PlayState::Instance()->p_sum);//�÷��̾��� ī�� �̱�
}
void PlayState::stand() {
	
	for (int i = 0; PlayState::Instance()->c_sum < 17; i++) {
		PlayState::Instance()->draw(&PlayState::Instance()->x_, &PlayState::Instance()->y_, &PlayState::Instance()->c_sum);//��ǻ���� ī�� �̱�
	}
	PlayState::Instance()->result();//������ ���� ���� �Լ�
}
void PlayState::draw(int *x, int *y, int *sum) {
	re:
	num = rand() % 13;
	if (card_jungbok[num] > 3)//ī�� �ߺ��� 3���� ������ �ٽ�
		goto re;
	else
		switch (num)
		{
		case 0: {m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card1")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 1: {m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card2")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 2: {m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card3")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 3: {m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card4")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break;	}
		case 4: { m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card5")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 5: { m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card6")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 6: {m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card7")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 7: { m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card8")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 8: { m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card9")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 9: {m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card10")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 10: {m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card11")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break;		}
		case 11: { m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card12")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		case 12: { m_gameObjects.push_back(new Player(new LoaderParams(*x, *y, 48, 72, "card13")));
			*x += 68; *sum += (num + 1); card_jungbok[num]++; break; }
		}
	SDL_Delay(100);
	std::cout <<p_sum <<' '<< c_sum << std::endl;
	for (int i = 0; i < 13; i++) {
		std::cout << "card"<<i<<"=" << card_jungbok[i] << std::endl;
	}
}
void PlayState::result() {//���� ���� �Լ�

    if (c_sum > 21 && p_sum <= 21)
	{
		Enemy::Instance()->text = TTF_RenderText_Solid(font, "Win ", color);
		Money += (GameOverState::Instance()->betamount * 2);
		TheGame::Instance()->getStateMachine()->changeState(Enemy::Instance());
	}
	else if (p_sum > c_sum)
	{
		Enemy::Instance()->text = TTF_RenderText_Solid(font, "Win ", color);
		Money += (GameOverState::Instance()->betamount * 2);
		TheGame::Instance()->getStateMachine()->changeState(Enemy::Instance());
	}
	else if (p_sum < c_sum)
	{
		Enemy::Instance()->text = TTF_RenderText_Solid(font, "Lose ", color);
		TheGame::Instance()->getStateMachine()->changeState(Enemy::Instance());
	}
	else
	{
		Enemy::Instance()->text = TTF_RenderText_Solid(font, "Draw ", color);
		Money += GameOverState::Instance()->betamount;
		TheGame::Instance()->getStateMachine()->changeState(Enemy::Instance());
	}
}
void PlayState::sum() {//�ؽ�Ʈ ��� �Լ�
	char s[256];
		char ss[256],ms[256];// �ؽ�Ʈ ���� ���ڿ�
	sprintf_s(ss, "%d", p_sum);//p_sum�� ���ڿ��� ��ȯ
	strcpy_s(s, 256, "Sum=");
	//s = (char*)malloc(strlen(ss) + 1);
	strcat_s(s,sizeof(s), ss);
	strcpy_s(ms, 256, "Money=");
	sprintf_s(ss, "%d",Money); 
	strcat_s(ms, sizeof(ms), ss);
	text = TTF_RenderText_Solid(font, s, color);
	moneytext = TTF_RenderText_Solid(font, ms, color);
	texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), text);
	moneytexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), moneytext);
	SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
	SDL_QueryTexture(moneytexture, NULL, NULL, &msrcRect.w, &msrcRect.h);
	start = true;
}