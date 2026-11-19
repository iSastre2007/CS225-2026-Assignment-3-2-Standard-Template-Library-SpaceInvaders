#include "DestroiableBlock.h"
#include "src/Components/position_component.hh"
#include <AEEngine.h>

DestroiableBlock::DestroiableBlock()
{
	mx = 0;
	my = 0;
	attach(new PositionComponent((int)mx, (int)my));
}

void DestroiableBlock::Update()
{

	//Update our component
	updatePositionComponent();
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

void DestroiableBlock::updatePositionComponent()
{
	PositionComponent* pc = static_cast<PositionComponent*>(getComponent("Position"));
	if (pc)
		pc->setPosition((int)mx, (int)my);
}
