#include "Player.h"
#include "src/Components/position_component.hh"
#include <AEEngine.h>

Player::Player(float posX, float posY, int maxBullets) : inputHandler(this, &Player::onInput), collisionHandler(this, &Player::onCollision), mx(posX), my(posY)
{
	attach(new PositionComponent((int)posX, (int)posY));

	for (int i = 0; i < maxBullets; i++)
		bullets.push_back(new Bullet());

	mLives = 3; //Hardcode just 3 lives
}

Player::~Player()
{
	std::for_each(bullets.begin(), bullets.end(), [](Bullet* b)->void {delete b; });
	bullets.clear();
}

void Player::Update()
{
	//Get delta time and move
	float dt = (float)AEGetFrameTime();
	mx += mDirection * speed * dt;

	//Clamp position to not get out of screen
	float limit = AEGetSysWindowWidth() / 2.0f - width / 2.0f;
	if (mx > limit)
		mx = limit;
	else if (mx < -limit)
		mx = -limit;

	//Update our component
	updatePositionComponent();

	//Update bullets
	std::for_each(bullets.begin(), bullets.end(), [](Bullet* b)->void { b->Update(); });
}

void Player::Draw()
{
	AEGfxRect(mx, my, 0, width, height, AEGfxColor(255, 255, 255));

	//Draw bullets
	std::for_each(bullets.begin(), bullets.end(), [](Bullet* b)->void { b->Draw(); });
}

void Player::onInput(inputEvent* e)
{
	if (e->mInput == MoveRight)
		mDirection = 1;
	else if (e->mInput == MoveLeft)
		mDirection = -1;
	else if (e->mInput == Still)
		mDirection = 0;
	else if (e->mInput == Shoot)
		ShootBullet();
}

IEventHandler* Player::getInputHandler()
{
	return &inputHandler;
}

std::vector<Bullet*>& Player::getBullets()
{
	return bullets;
}

void Player::onCollision(collisionEvent* e)
{
	if (e->collisionType == BulletPLayer)
	{
		mLives--;
		mx = 0;
	}
	if (mLives == 0)
	{
		AESetGameStateNext(AE_GS_RESTART);
	}
	if(e->collisionType == AlienPlayer)
		AESetGameStateNext(AE_GS_RESTART);
}

IEventHandler* Player::getCollisionHandler()
{
	return &collisionHandler;
}

float Player::getX()
{
	return mx;
}

float Player::getY()
{
	return my;
}

float Player::getWidth()
{
	return width;
}

float Player::getHeight()
{
	return height;
}

int Player::getLives()
{
	return mLives;
}

void Player::updatePositionComponent()
{
	PositionComponent* pc = static_cast<PositionComponent*>(getComponent("Position"));
	if (pc)
		pc->setPosition((int)mx, (int)my);
}

void Player::ShootBullet()
{
	auto it = std::find_if(bullets.begin(), bullets.end(), [](Bullet* b)->bool {return b->getReady(); });
	if (it != bullets.end())
		(*it)->placeBullet(mx, my, 1); //1 because we know this is the player so the bullet must go up
}
