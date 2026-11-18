#include "InputManager.h"
#include <AEEngine.h>
#include "customEvents.h"

void inputEventManager::update()
{
	//Check keyboard
	bool left = AEInputKeyPressed('A');
	bool right = AEInputKeyPressed('D');
	bool shoot = AEInputKeyPressed(' ');

	//Get inputs
	Input input = Still;
	if (left)
		input = MoveLeft;
	else if (right)
		input = MoveRight;
	else if (shoot)
		input = Shoot;

	//Create and trhow the event	
	inputEvent e(input);
	notifyEvent(&e);
}

