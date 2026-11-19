#pragma once
#include "Bullet.h"
#include <src/Framework/entity.hh>
#include "src/Events/customEvents.h"
#include <src/Framework/event_handlers.hh>

//Player class
class Player : public Entity
{
public:
	float width = 20.0f;
	float height = 20.0f;
	float speed = 400.0f;

	Player(float posX, float posY, int maxBullets);
	~Player();

	void Update() override;
	void Draw() override;

	//Recive the inputs
	void onInput(inputEvent* e);
	IEventHandler* getInputHandler();
	std::vector<Bullet*>& getBullets();

	//Check collisions
	void onCollision(collisionEvent* e);
	IEventHandler* getCollisionHandler();

	//Gettors
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	int getLives();

	//Update position component
	void updatePositionComponent();

private:
	//Event handler where all inputs will be passed to
	EventHandler<Player, inputEvent> inputHandler;
	//Event handler where all collisions will be passed to
	EventHandler<Player, collisionEvent> collisionHandler;

	//Vector of all player bullets
	std::vector<Bullet*> bullets;
	void ShootBullet();

	//position in world
	float mx, my;
	float mDirection = 0; //Direction where to go (right +1, left -1)
	int mLives = 3;
};
