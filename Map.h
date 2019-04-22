#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "GLManager.h"
#include "fstream"

class Map {
private:
	int x_size, y_size;
	Tile** tiles;

public:
	Map(int x, int y);
	~Map();

	static Map* loadMap(int mapNum);
	void display();
	Tile* getTile(int x, int y);
	void setTile(int tilesInd, Tile* tile);
};

#endif