#include "DestroiableBlock.h"
#include "src/Components/position_component.hh"
#include <AEEngine.h>

DestroiableBlock::DestroiableBlock(float posX, float posY) : collisionHandler(this, &DestroiableBlock::OnCollision)
{
	mx = posX;
	my = posY;
}

void DestroiableBlock::Update()
{
}

void DestroiableBlock::Draw()
{
	//Just draw if it has been shot
	AEGfxRect(mx, my, 0, width, height, AEGfxColor(255, 255, 255));
}

float DestroiableBlock::getX()
{
	return mx;
}

float DestroiableBlock::getY()
{
	return my;
}

float DestroiableBlock::getWidth()
{
	return width;
}

float DestroiableBlock::getHeight()
{
	return height;
}

void DestroiableBlock::OnCollision(collisionEvent* e)
{
	if (e->collisionType == BulletBlock)
	{
		if (height > 0)
			height -= initialHeight / 5;
	}
}
