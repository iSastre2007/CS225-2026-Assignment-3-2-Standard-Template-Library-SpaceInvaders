#include "CollisionManager.h"
#include <AEEngine.h>
#include "src/Game/Player.h"
#include "src/Game/Aliens.h"

collisionEventManager::collisionEventManager(Player* player, std::vector<Alien*> aliens) : mPlayer(player), mAliens(aliens)
{
}

void collisionEventManager::update()
{
	//Data to work with
	float halfWindowWidth = AEGetSysWindowWidth() / 2;
	float px = mPlayer->getX();
	float py = mPlayer->getY();
	float ph = mPlayer->getHeight();
	float pw = mPlayer->getWidth();
	AEVec2 playerPos(px, py);

	//Lambda to check collision between an alien and the player
	auto checkAndResolveCol = [&](Alien* a) -> void {
		AEVec2 alienPos(a->getX(), a->getY());
		if (AEStaticRectToStaticRect(&playerPos, pw, ph, &alienPos, a->getWidth(), a->getHeight()))
		{
			isCollision(AlienPlayer);
		}
	};

	//Lambda to check when aliens hit wall bounds
	auto checkBounds = [&](Alien* a) -> void {
		if (a->getX() >= halfWindowWidth || a->getX() <= -halfWindowWidth)
			a->changeDir();
	};

	//Check collision with player and aliens
	std::for_each(mAliens.begin(), mAliens.end(), checkAndResolveCol);

	//Check collision aliens with limits
	std::for_each(mAliens.begin(), mAliens.end(), checkBounds);
}

void collisionEventManager::isCollision(colType ct)
{
	collisionEvent e(ct);
	notifyEvent(&e);
}
