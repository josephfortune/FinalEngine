#include "Character.h"
#include <math.h>

#define PIOVER2 1.57079632679

Character::Character(void)
{
	pos = Vector2(0, 0);
	direction = Vector2(0, 1);
	speed = 2;
}

void Character::moveFwd(void)
{
	pos = pos + (direction * speed);
}

void Character::moveBack(void)
{
	pos = pos - (direction * speed);
}

void Character::turnLeft(void)
{
	angle -= 0.05;
	updateDirection();
}

void Character::turnRight(void)
{
	angle += 0.05;
	updateDirection();
}

Vector2 Character::getDirection(void)
{
	return direction;
}

Vector2 Character::getPos(void)
{
	return pos;
}

void Character::updateDirection(void)
{
	direction = Vector2(-cos(angle + PIOVER2), sin(angle + PIOVER2));
}

double Character::getAngle(void)
{
	return angle;
}

Sector* Character::getSector()
{
	return sector;
}

void Character::setSector(Sector *sector)
{
	Character::sector = sector;
}


