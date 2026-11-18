#include "Aliens.h"
#include "src/Components/position_component.hh"
#include <AEEngine.h>

Alien::Alien(int row, float posX) : collisionHandler(this, &Alien::onWallHit)
{
	mRow = row;
	mx = posX;
	my = 250 - verticalDisplacement * row;
	attach(new PositionComponent((int)mx, (int)my));
}

void Alien::Update()
{
	if (!mAlive)
		return;
	//Get delta time and move
	float dt = (float)AEGetFrameTime();
	mx += mDirection * speed * dt;


	//Update our component
	updatePositionComponent();
}

void Alien::Draw()
{
	if (!mAlive)
		return;
	AEGfxRect(mx, my, 0, width, height, AEGfxColor(255 * mRow/ 5, 255 - (255 * mRow / 5), 255 * mRow / 5));
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

void Alien::setAlive(bool a)
{
	mAlive = a;
}

bool Alien::getAlive()
{
	return mAlive;
}

void Alien::onWallHit(collisionEvent* e)
{
	if (e->collisionType == AlienWall)
	{
		mDirection *= -1;
		my -= verticalDisplacement / 5.0f; // Divided by 5 so they dont take a big step downwards
	}
}

IEventHandler* Alien::getCollisionHandler()
{
	return &collisionHandler;
}

void Alien::updatePositionComponent()
{
	PositionComponent* pc = static_cast<PositionComponent*>(getComponent("Position"));
	if (pc)
		pc->setPosition((int)mx, (int)my);
}
