#include "Bullet.h"
#include "src/Components/position_component.hh"
#include <AEEngine.h>

Bullet::Bullet()
{
	mx = 0;
	my = 0;
	attach(new PositionComponent((int)mx, (int)my));
}

void Bullet::Update()
{
	//Cooldown
	if (mReady == false)
	{
		float dt = (float)AEGetFrameTime();
		timer += dt;
		if (timer > cooldown)
		{
			timer = 0.0f;
			mReady = true;
			mAlive = false;
		}
	}

	//Just move if it has been shot
	if (mAlive == false)
		return;

	//Get delta time and move
	float dt = (float)AEGetFrameTime();
	my += mDirection * speed * dt;

	//Update our component
	updatePositionComponent();
}

void Bullet::Draw()
{
	//Just draw if it has been shot
	if (mAlive == false)
		return;
	AEGfxRect(mx, my, 0, width, height, AEGfxColor(255, 255, 255));
}

float Bullet::getX()
{
	return mx;
}

float Bullet::getY()
{
	return my;
}

float Bullet::getWidth()
{
	return width;
}

float Bullet::getHeight()
{
	return height;
}

bool Bullet::getAlive()
{
	return mAlive;
}

void Bullet::setAlive(bool a)
{
	mAlive = a;
}

bool Bullet::getReady()
{
	return mReady;
}

void Bullet::updatePositionComponent()
{
	PositionComponent* pc = static_cast<PositionComponent*>(getComponent("Position"));
	if (pc)
		pc->setPosition((int)mx, (int)my);
}

void Bullet::placeBullet(float posX, float posY, int dir)
{
	mx = posX;
	my = posY;
	mDirection = dir;
	mReady = false;
	mAlive = true;
}
