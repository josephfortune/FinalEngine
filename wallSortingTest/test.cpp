#include <stdio.h>
#include "Wall.h"

void printWall(Wall w)
{
	printf("<%.1f , %.1f> <%.1f, %.1f>\n", w.v1.x, w.v1.y, w.v2.x, w.v2.y);
}

int main()
{
	Wall w1(-6,-3, -10, 1, false);
	Wall w2(-6, -2, -4, 2, false);

	Wall *closest = Wall::closer(&w1, &w2);
	if (closest == NULL) printf("No sort needed\n");
	else printWall(*closest);
}
