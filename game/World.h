#ifndef WORLD_H
#define WORLD_H

#include "Wall.h"
#include "Character.h"
#include "Scene.h"
#include "Sector.h"

class World
{
	public:
	World();
	void setPlayer(Character* player_in);
	Character* getPlayer();
	Scene getScene(Sector* sector);
	void setWallsPtr(Wall* walls, int nWalls_in);
	void setSectorsPtr(Sector* sectors, int nSectors);
	void moveCharacter(Character* c, int direction);

	protected:
	Wall* walls;
	int nWalls;
	Sector* sectors;
	int nSectors;
	Character* player;
	Scene scene;
	// add textures
	// add entities
};

#endif
