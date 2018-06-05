#ifndef SCENE_H
#define SCENE_H

#include "Wall.h"
#include "Sector.h"

#define MAX_WALLS 256

class Scene
{
	public:
	Scene( void ) : numWalls( 0 ) {};
	void addWall( Wall wall );
	void addSector(Sector *	sector);
	int getNumWalls();
	Wall* wallAt( int index );
	void transform( double angle, double dx, double dy );
	void reset();

	//protected:
	Wall walls[MAX_WALLS];
	int numWalls;
};

#endif
