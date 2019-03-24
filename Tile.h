#ifndef TILE_H
#define TILE_H

#include "Hitbox.h"
#include "GLManager.h"

class Tile {
private:
	Hitbox** hitboxes; // Tile may have multiple hitboxes

public:
	Tile();
	~Tile();
	
	void display();
};

#endif