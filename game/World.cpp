#include "World.h"

World::World() {}


void World::setPlayer(Character *player_in)
{
	player = player_in;
}

Character* World::getPlayer()
{
	return player;
}

void World::setWallsPtr(Wall* walls_in, int nWalls_in)
{
	walls = walls_in;
	nWalls = nWalls_in;
}

void World::setSectorsPtr(Sector* pSectors, int nSectors)
{
	sectors = pSectors;
	World::nSectors = nSectors;
}

Scene World::getScene(Sector *sector)
{
	// Later we will cut and sort the walls here

	scene.reset();

	int nSectorWalls = sector->nWalls;
	Wall* pWalls = sector->walls;
	

	for (int i = 0; i < nSectorWalls; i++)
	{
		// Only add walls that are in front of the players POV
		if (pWalls[i].normal * (player->getPos() - pWalls[i].v1) > 0)
			scene.addWall(pWalls[i]);
	}

	scene.transform( player->getAngle(), -player->getPos().x, -player->getPos().y);

	return scene;
}

void World::moveCharacter(Character* c, int direction)
{
	if (direction == DIRECTION_FWD)
	{
		// Later we will collision detect here
		c->moveFwd();
	}
	if (direction == DIRECTION_BACK)
	{
		// Later we will collision detect here
		c->moveBack();
	}

	// Has character left the sector?
	if (!c->getSector()->isInside(c->getPos()))
	{
		for (int i = 0; i < nSectors; i++)
		{
			if (sectors[i].isInside(c->getPos()))
			{
				c->setSector(&sectors[i]);
			}
		}
	}
}
