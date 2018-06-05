#include "Controller.h"

Controller::Controller(Inputs *inputs_in, World *world_in)
{
	input = inputs_in;
	world = world_in;
}

void Controller::processInputs()
{
	if (input->isSetMovFwd())
	{
		world->moveCharacter(world->getPlayer(), DIRECTION_FWD);
	}
	if (input->isSetMovBack())
	{
		world->moveCharacter(world->getPlayer(), DIRECTION_BACK);
	}
	if (input->isSetTurnLeft())
	{
		world->getPlayer()->turnLeft();
	}
	if (input->isSetTurnRight())
	{
		world->getPlayer()->turnRight();
	}
	
	//input->reset();
}
