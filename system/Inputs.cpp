#include "Inputs.h"

Inputs::Inputs(void)
{
	reset();
}

void Inputs::setMovFwd() {movFwd = true;}
void Inputs::setMovBack() {movBack = true;}
void Inputs::setTurnLeft() {turnLeft = true;} 
void Inputs::setTurnRight() {turnRight = true;}

void Inputs::unSetMovFwd() {movFwd = false;}
void Inputs::unSetMovBack() {movBack = false;}
void Inputs::unSetTurnLeft() {turnLeft = false;} 
void Inputs::unSetTurnRight() {turnRight = false;}

bool Inputs::isSetMovFwd() {return movFwd;}
bool Inputs::isSetMovBack() {return movBack;}
bool Inputs::isSetTurnLeft() {return turnLeft;}
bool Inputs::isSetTurnRight() {return turnRight;}

void Inputs::reset()
{
	movFwd = movBack = turnLeft = turnRight = false;
}
