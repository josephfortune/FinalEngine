#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Inputs.h"
#include "../game/World.h"

class Controller
{
	public:
	Controller(Inputs *inputs_in, World *world_in);
	void processInputs();	

	private:
	Inputs *input;
	World *world;

};

#endif
