#include "Sector.h"
#include <stdio.h>

void Sector::setWalls(Wall* wallPtr, int numWalls)
{
	walls = wallPtr;
	nWalls = numWalls;
}

bool Sector::isInside(Vector2 pos)
{
	int intersections = 0;
	Vector2 leftPointing(-1, 0); // Intersection ray checks walls to the left of pos

	for (int i = 0; i < nWalls; i++)
	{
		Vector2 a = walls[i].v1;
		Vector2 b = walls[i].v2;
	
		/*
		if (leftPointing * walls[i].normal > 0) // (dot product) Only check walls to the right
		{
			if (a.y > b.y && a.y > pos.y && b.y < pos.y) intersections++;
			else if (a.y < pos.y && b.y > pos.y) intersections++;
		}*/

		if (a.y > b.y && a.y > pos.y && b.y < pos.y || a.y < pos.y && b.y > pos.y)
		{			
			if (Vector2::rayIntersect( pos, leftPointing, walls[i].v1, walls[i].v2 - walls[i].v1).x - pos.x > 0)
			intersections++;
		}
	}

	return intersections > 0 && (intersections % 2); // True if an odd number (means inside polygon)
}
