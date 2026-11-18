#include "Aliens.h"
#include "src/Components/position_component.hh"
#include <AEEngine.h>

Alien::Alien(float posX, float posY) : inputHandler(this, &Alien::onInput), mx(posX), my(posY)
{
	attach(new PositionComponent(posX, posY));
}

void Alien::Update()
{
	//Get delta time and move
	float dt = AEGetFrameTime();
	my += mDirection * speed * dt;

	//Clamp position to not get out of screen
	float limit = AEGetSysWindowHeight() / 2.0f - height / 2.0f;
	if (my > limit)
		my = limit;
	else if (my < -limit)
		my = -limit;

	//Update our component
	updatePositionComponent();
}

void Alien::Draw()
{
	AEGfxRect(mx, my, 0, width, height, AEGfxColor(255, 255, 255));
}

void Alien::onInput(inputEvent* e)
{
	if (e->mInput == MoveRight)
		mDirection = 1;
	else if (e->mInput == MoveLeft)
		mDirection = -1;
	else if (e->mInput == Still)
		mDirection = 0;
}

IEventHandler* Alien::getInputHandler()
{
	return &inputHandler;
}

float Alien::getX()
{
	return mx;
}

float Alien::getY()
{
	return my;
}

float Alien::getWidth()
{
	return width;
}

float Alien::getHeight()
{
	return height;
}

void Alien::updatePositionComponent()
{
	PositionComponent* pc = static_cast<PositionComponent*>(getComponent("Position"));
	if (pc)
		pc->setPosition(mx, my);
}

void Alien::changeDir()
{
	mDirection *= -1;
	my -= verticalDisplacement;
}
