#include "Scene.h"
#include "../maths/Matrix2.h"

void Scene::addWall( Wall wall )
{
	if ( numWalls + 1 < MAX_WALLS )	
		walls[numWalls++] = wall;
}

int Scene::getNumWalls( void )
{
	return numWalls;
}

Wall* Scene::wallAt( int index )
{
	return &walls[index];
}

void Scene::transform( double angle, double dx, double dy )
{
	Matrix2 transform = Matrix2::getRotateMatrix( angle ) * Matrix2::getTransMatrix( dx, dy );

	for ( int i = 0; i < numWalls; i++ )
	{
		// Transform the wall vertices
		walls[i] = Wall( transform * walls[i].v1, transform * walls[i].v2, walls[i].nextSector );	
	}
}

void Scene::reset()
{
	numWalls = 0;
}

void Scene::addSector(Sector* sector)
{
	int nSectorWalls = sector->nWalls;
	Wall* pWalls = sector->walls;

	for (int i = 0; i < nSectorWalls; i++)
	{
		addWall(pWalls[i]);
	}
}
