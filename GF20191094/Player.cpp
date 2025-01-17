#include"Player.h"
#include"SDLGameObject.h"
#include"InputHandler.h"
Player::Player(const LoaderParams* pParams) :SDLGameObject(pParams) {}

void Player::draw() {
	SDLGameObject::draw();
}
void Player::update() {
	//handleInput();
	m_currentFrame = int(((SDL_GetTicks() / 100) % 1));
	//m_acceleration.setX(1);
	SDLGameObject::update();
}
void Player::handleInput() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		m_velocity.setX(2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		m_velocity.setX(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		m_velocity.setY(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		m_velocity.setY(2);
	}
}