#pragma once
#include <src/Framework/entity.hh>
#include "src/Events/customEvents.h"
#include <src/Framework/event_handlers.hh>

#define BLOCK_WIDTH 55.0f

class DestroiableBlock : public Entity
{
public:
	float width = BLOCK_WIDTH;
	const float initialHeight = 30.0f;
	float height = initialHeight;

	DestroiableBlock(float posX, float posY);

	void Update() override;
	void Draw() override;

	//Gettors
	float getX();
	float getY();
	float getWidth();
	float getHeight();

	void OnCollision(collisionEvent* e);


private:
	//Event handler where all collisions will be passed to
	EventHandler<DestroiableBlock, collisionEvent> collisionHandler;

	float mx, my;
};
