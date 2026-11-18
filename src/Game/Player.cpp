#include "Player.h"
#include "src/Components/position_component.hh"
#include <AEEngine.h>

Player::Player(float posX, float posY) : inputHandler(this, &Player::onInput), mx(posX), my(posY)
{
	attach(new PositionComponent(posX, posY));
}

void Player::Update()
{
	//Get delta time and move
	float dt = AEGetFrameTime();
	mx += mDirection * speed * dt;

	//Clamp position to not get out of screen
	float limit = AEGetSysWindowWidth() / 2.0f - width / 2.0f;
	if (mx > limit)
		mx = limit;
	else if (mx < -limit)
		mx = -limit;

	//Update our component
	updatePositionComponent();
}

void Player::Draw()
{
	AEGfxRect(mx, my, 0, width, height, AEGfxColor(255, 255, 255));
}

void Player::onInput(inputEvent* e)
{
	if (e->mInput == MoveRight)
		mDirection = 1;
	else if (e->mInput == MoveLeft)
		mDirection = -1;
	else if (e->mInput == Still)
		mDirection = 0;
}

IEventHandler* Player::getInputHandler()
{
	return &inputHandler;
}

float Player::getX()
{
	return mx;
}

float Player::getY()
{
	return my;
}

float Player::getWidth()
{
	return width;
}

float Player::getHeight()
{
	return height;
}

void Player::updatePositionComponent()
{
	PositionComponent* pc = static_cast<PositionComponent*>(getComponent("Position"));
	if (pc)
		pc->setPosition(mx, my);
}
