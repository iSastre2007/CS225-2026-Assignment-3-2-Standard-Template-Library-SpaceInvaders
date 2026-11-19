#pragma once
#include "Bullet.h"
#include <src/Framework/entity.hh>
#include "src/Events/customEvents.h"
#include <src/Framework/event_handlers.hh>

//Alien class
class Alien : public Entity
{
public:
	float width = 30.0f;
	float height = 25.0f;
	float speed = 25.0f;
	const float incrementSpeed = 5.0f;
	const float verticalDisplacement = 30.0f;

	Alien(int row, float posX);

	void Update() override;
	void Draw() override;

	//Gettors
	float getX();
	float getY();
	float getWidth();
	float getHeight();

	//Set the modes of the alien (alive = false means death)
	void setAlive(bool a);
	bool getAlive();

	//Shooting function
	void Shoot(Bullet* b);

	//Event to descend
	void onWallHit(collisionEvent* e);
	IEventHandler* getCollisionHandler();

	//Update position component
	void updatePositionComponent();

private:
	//Event handler where all collisions will be passed to
	EventHandler<Alien, collisionEvent> collisionHandler;

	//position in world
	bool mAlive = true;
	int mRow;
	float mx, my;
	float mDirection = 1; //Direction where to go (right +1, left -1)
};
