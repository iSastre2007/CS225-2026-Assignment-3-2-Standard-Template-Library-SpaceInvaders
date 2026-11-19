#include "CollisionManager.h"
#include <AEEngine.h>
#include "src/Game/Player.h"
#include "src/Game/Aliens.h"

collisionEventManager::collisionEventManager(Player* player, std::vector<Alien*> aliens, Bullet* b, std::vector<DestroiableBlock*> blocks) : 
	mPlayer(player), mAliens(aliens), mAlienBullet(b), mBlocks(blocks)
{
}

void collisionEventManager::update()
{
	//Data to work with
	float halfWindowWidth = AEGetSysWindowWidth() / 2.0f;

	//Player
	float px = mPlayer->getX();
	float py = mPlayer->getY();
	float ph = mPlayer->getHeight();
	float pw = mPlayer->getWidth();
	AEVec2 playerPos(px, py);

	//Alien
	float abx = mAlienBullet->getX();
	float aby = mAlienBullet->getY();
	float abh = mAlienBullet->getHeight();
	float abw = mAlienBullet->getWidth();
	AEVec2 aBulletPos(abx, aby);

	//Lambda to check collision between an alien and the player
	auto checkAndResolveCol = [&](Alien* a) -> void {
		AEVec2 alienPos(a->getX(), a->getY());
		if (AEStaticRectToStaticRect(&playerPos, pw, ph, &alienPos, a->getWidth(), a->getHeight()))
		{
			isCollision(AlienPlayer);
		}
	};

	//Lambda to check when aliens hit wall bounds
	//The resolution of this collision is made here for simplicity purposes
	auto checkBounds = [&](Alien* a) -> bool {
		if (a->getAlive() == false) //Not check if its dead
			return false;
		if (a->getX() >= halfWindowWidth || a->getX() <= -halfWindowWidth)
			return true;
		return false;
		};

	//Lambda to check when a player bullet hits an alien
	auto checkPLayerBulletAlien = [&](Alien* a) -> void {
		std::for_each(mPlayer->getBullets().begin(), mPlayer->getBullets().end(), [&](Bullet* b)->void { //Create another lambda to check for every
			if (b->getAlive() == false || a->getAlive() == false) return;								 //bullet inside the player bullets vector
			AEVec2 bulletPos(b->getX(), b->getY());
			AEVec2 alienPos(a->getX(), a->getY());
			if (AEStaticRectToStaticRect(&bulletPos, b->getWidth(), b->getHeight(), &alienPos, a->getWidth(), a->getHeight()))
			{
				a->setAlive(false);
				b->setAlive(false);
				isCollision(AlienBullet);
			}
			});
		};

	//PLAYER - ALIENS
	std::for_each(mAliens.begin(), mAliens.end(), checkAndResolveCol);

	//ALIENS - WALL
	if (std::any_of(mAliens.begin(), mAliens.end(), checkBounds))
		isCollision(AlienWall);

	//ALIENS - PLAYER BULLET
	std::for_each(mAliens.begin(), mAliens.end(), checkPLayerBulletAlien);

	//ALIENS BULLET - PLAYER
	if (AEStaticRectToStaticRect(&playerPos, pw, ph, &aBulletPos, abw, abh))
	{
		isCollision(BulletPLayer);
	}
}

void collisionEventManager::isCollision(colType ct)
{
	collisionEvent e(ct);
	notifyEvent(&e);
}
