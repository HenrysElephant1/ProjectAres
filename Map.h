#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "GLManager.h"

class Map {
private:
	int x_size, y_size;
	Tile** tiles;

public:
	Map();
	~Map();

	void display();
};

#endif