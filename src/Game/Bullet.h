#pragma once
#include <src/Framework/entity.hh>
#include "src/Events/customEvents.h"
#include <src/Framework/event_handlers.hh>

class Bullet : public Entity
{
public:
	float width = 5.0f;
	float height = 10.0f;
	float speed = 600.0f;

	Bullet();

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
	float timer = 0.0f;

	const float cooldown = 3.0f; //3 seconds for a bullet to recharge
	bool mAlive = false; //Lets know when it is flying
	bool mReady = true; //Lets know when it can be shot
	float mx, my;
	int mDirection = 0; //Direction where to go (up +1, down -1)
};
