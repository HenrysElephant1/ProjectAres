#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include "Hitbox.h"
#include "Tile.h"
#include "GLManager.h"

class TileFactory {
private:
    
public:
	static Tile* createWallTile(int xpos, int ypos, int texture);
    static Tile* createFloorTile(int xpos, int ypos, int texture);
};

#endif