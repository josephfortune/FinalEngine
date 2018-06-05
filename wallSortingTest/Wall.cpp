#include "Wall.h"

Wall::Wall( float x1, float y1, float x2, float y2, bool portal )
{
	// Init the vectors describing the wall vertices	
	v1.x = x1;
	v1.y = y1;
	v2.x = x2;
	v2.y = y2;
	isPortal = portal;
	
	direction = v2 - v1;	// Form vector from walls vertices
	normal = Vector2( direction.y, -direction.x ); // Perpendicular to wall
	length = direction.length();
}

Wall::Wall(){}

Wall::Wall ( Vector2 vertex1, Vector2 vertex2 )
{
	v1 = vertex1;
	v2 = vertex2;

	direction = v2 - v1;	// Form vector from walls vertices
	normal = Vector2( direction.y, -direction.x ); // Perpendicular to wall
	length = direction.length();
}


#define CLOSER_A 0
#define CLOSER_B 1
#define CLOSER_INDETERMINATE 2
#define CLOSER_SORT_NOT_NEEDED 3

int Wall::closerTest(Wall a, Wall b)
{
	float dx, dy;
	float dot1, dot2;

	// How far from the reference vertex to the origin
	dx = -a.v1.x;
	dy = -a.v1.y;

	// Shift Wall 1 to origin
	a.v1.x = 0;
	a.v1.y = 0;
	a.v2.x += dx;
	a.v2.y += dy;

	// Shift wall 2
	b.v1.x += dx;
	b.v1.y += dy;
	b.v2.x += dx;
	b.v2.y += dy;

	// Dot the walls normal vector with the opposing walls vertices
	dot1 = a.normal * b.v1;
	dot2 = a.normal * b.v2;

	if (dot1 * dot2 == 0) return CLOSER_SORT_NOT_NEEDED;
	if (dot1 * dot2 < 0) return CLOSER_INDETERMINATE;
	if (dot1 > 0 && dot2 > 0) return CLOSER_B;
	if (dot1 < 0 && dot2 < 0) return CLOSER_A;
}


Wall* Wall::closer(Wall *w1, Wall *w2)
{
	Wall a = *w1; // Were going to transform the walls for the test, so we need copies.
	Wall b = *w2;
	
	int result = closerTest(a, b);

	// If indeterminate, test from other wall. if CLOSER_NOT_NEEDED, double check from the other wall to make sure
	// sure the test isn't misguided by false result (ex. walls [<-7, 8> <-4, 8>] and [<-6, 6>, <-3, 8>] )
	if (result == CLOSER_SORT_NOT_NEEDED || result == CLOSER_INDETERMINATE) 
	{
		result = closerTest(b, a);

		if (result == CLOSER_SORT_NOT_NEEDED) return NULL;
		if (result == CLOSER_A) return w2;
		if (result == CLOSER_B) return w1;
	}
	else
	{
		if (result == CLOSER_SORT_NOT_NEEDED) return NULL;
		if (result == CLOSER_A) return w1;
		if (result == CLOSER_B) return w2;
	}
}



