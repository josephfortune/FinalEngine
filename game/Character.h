#ifndef CHARACTER_H
#define CHARACTER_H

#include "../maths/Vector2.h"
#include "../maths/Matrix2.h"
#include "Sector.h"

#define DIRECTION_FWD 0
#define DIRECTION_BACK 1

class Character
{
	public:
	Character();
	void moveFwd();
	void turnLeft();
	void turnRight();
	void moveBack();
	Vector2 getDirection();
	Vector2 getPos();
	void updateDirection(); //Creates the direction vector from the angle when needed
	double getAngle();
	Sector* getSector();
	void setSector(Sector *sector);


	Vector2 pos;
	Vector2 direction;
	double speed;
	double angle;
	Sector *sector;

};

#endif
