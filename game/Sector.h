#ifndef SECTOR_H
#define SECTOR_H

#include "Wall.h"
#include "../maths/Vector2.h"


class Sector
{
	public:
	void setWalls(Wall* wallPtr, int numWalls);
	bool isInside(Vector2 pos);

	int nWalls;
	Wall* walls;
};

#endif
