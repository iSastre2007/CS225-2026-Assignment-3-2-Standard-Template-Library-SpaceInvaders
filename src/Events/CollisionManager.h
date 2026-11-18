#pragma once
#include "src/Framework/event_handlers.hh"
#include "customEvents.h"

//Forward declaration
class Player;
class Alien;

class collisionEventManager : public EventManager
{
public:
	collisionEventManager(Player* player, std::vector<Alien*> aliens);

	//Check for collisions
	void update() override;

private:
	Player* mPlayer;
	std::vector<Alien*> mAliens;

	void isCollision(colType ct);
};
