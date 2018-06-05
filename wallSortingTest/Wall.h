#ifndef WALL_H
#define WALL_H

#include "Vector2.h"


class Wall
{
	public:
	Wall( float x1, float y1, float x2, float y2, bool portal );
	Wall ( Vector2 vertex1, Vector2 vertex2 );
	Wall ();

	static Wall* closer(Wall *w1, Wall *w2); // Returns which wall is closer, assumes the walls are already transformed to player space

	Vector2 v1; // Vertex 1
	Vector2 v2; // Vertex 2
	Vector2 direction;	// Direction along wall, used for ray-intersections
	Vector2 normal;	// Direction perpendicular to wall, used for wall sorting
	float length;	// Wall length
	bool isPortal;

	private:
	static int closerTest(Wall a, Wall b);
};

#endif
