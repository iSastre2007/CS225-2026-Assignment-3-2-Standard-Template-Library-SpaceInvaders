#include "InputManager.h"
#include <AEEngine.h>
#include "customEvents.h"

void inputEventManager::update()
{
	//Check keyboard
	bool left = AEInputKeyPressed('A');
	bool right = AEInputKeyPressed('D');
	bool shoot = AEInputKeyTriggered(' ');

	//Get inputs
	Input input = Still;
	if (shoot)
		input = Shoot;
	else if (left)
		input = MoveLeft;
	else if (right)
		input = MoveRight;

	//Create and trhow the event	
	inputEvent e(input);
	notifyEvent(&e);
}

