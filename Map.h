#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "GLManager.h"
#include <fstream>

class Map {
private:
	int x_size, y_size;
	int p1StartRow, p1StartCol, p2StartRow, p2StartCol;
	Tile** tiles;

public:
	Map(int x, int y, int sr1, int sc1, int sr2, int sc2);
	~Map();

	static Map* loadMap(int mapNum);
	void display();
	Tile* getTile(int x, int y);
	void setTile(int tilesInd, Tile* tile);
	void testPlayerCollision( Player *p );
	void testProjectileCollision( Projectile *p );

	glm::vec3 getP1StartPos();
	glm::vec3 getP2StartPos();
	glm::vec3 getCenter();
};

#endif