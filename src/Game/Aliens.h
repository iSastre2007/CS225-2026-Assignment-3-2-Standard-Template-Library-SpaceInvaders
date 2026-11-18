#pragma once
#include <src/Framework/entity.hh>
#include "src/Events/customEvents.h"
#include <src/Framework/event_handlers.hh>

//Alien class
class Alien : public Entity
{
public:
	float width = 40.0f;
	float height = 25.0f;
	float speed = 400.0f;
	const float verticalDisplacement = 35.0f;

	Alien(float posX, float posY);

	void Update() override;
	void Draw() override;

	//Recive the inputs
	void onInput(inputEvent* e);
	IEventHandler* getInputHandler();

	//Gettors
	float getX();
	float getY();
	float getWidth();
	float getHeight();

	//Update position component
	void updatePositionComponent();
	void changeDir(); //Called when an alien must change direction

private:
	//Event handler where all inputs will be passed to
	EventHandler<Alien, inputEvent> inputHandler;

	//position in world
	float mx, my;
	float mDirection = 0; //Direction where to go (up +1, down -1)
};
