#pragma once
#include "src/Framework/event_handlers.hh"
#include "customEvents.h"

//Forward declaration
class Player;
class Alien;
class Bullet;
class DestroiableBlock;

class collisionEventManager : public EventManager
{
public:
	collisionEventManager(Player* player, std::vector<Alien*> aliens, Bullet* b, std::vector<DestroiableBlock*> blocks);

	//Check for collisions
	void update() override;

private:
	Player* mPlayer;
	std::vector<Alien*> mAliens;
	std::vector<DestroiableBlock*> mBlocks;
	Bullet* mAlienBullet;

	void isCollision(colType ct);
};
