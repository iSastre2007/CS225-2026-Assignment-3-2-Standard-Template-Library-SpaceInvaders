#pragma once
#include <src/Framework/entity.hh>
#include "src/Events/customEvents.h"
#include <src/Framework/event_handlers.hh>

class DestroiableBlock : public Entity
{
public:
	float width = 5.0f;
	float height = 10.0f;
	float speed = 600.0f;

	DestroiableBlock();

	void Update() override;
	void Draw() override;

	//Gettors
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	bool getAlive();
	void setAlive(bool a);
	bool getReady();

	//Update position component
	void updatePositionComponent();
	void placeBullet(float posX, float posY, int dir);

private:
	//Event handler where all collisions will be passed to
	EventHandler<DestroiableBlock, collisionEvent> collisionHandler;
	int subCells[4][5] = { {1, 1, 1, 1, 1},
						 {1, 1, 1, 1, 1},
						 {1, 1, 1, 1, 1},
						 {1, 1, 1, 1, 1},};

	float mx, my;
};
