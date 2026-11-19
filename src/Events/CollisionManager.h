#pragma once
#include "src/Framework/event_handlers.hh"
#include "customEvents.h"

//Forward declaration
class Player;
class Alien;
class Bullet;

class collisionEventManager : public EventManager
{
public:
	collisionEventManager(Player* player, std::vector<Alien*> aliens, Bullet* b);

	//Check for collisions
	void update() override;

private:
	Player* mPlayer;
	std::vector<Alien*> mAliens;
	Bullet* mAlienBullet;

	void isCollision(colType ct);
};
