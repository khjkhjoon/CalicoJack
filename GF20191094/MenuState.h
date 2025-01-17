#pragma once
#include "GameState.h"
#include <string>
class MenuState :public GameState {

public:
	static MenuState* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new MenuState();
		}
		return s_pInstance;
	}
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_menuID; }
private:
	static const std::string s_menuID;
	static void s_menuToPlay();
	static void s_exitFromMenu();
	MenuState() {}
	static MenuState* s_pInstance;

};