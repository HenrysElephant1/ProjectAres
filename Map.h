#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "GLManager.h"
#include <fstream>

const std::string mapFolder = "maps/";

class Map {
private:
	int x_size, y_size;
	int p1StartRow, p1StartCol, p2StartRow, p2StartCol;
	Tile** tiles;

public:
	Map(int x, int y, int sr1, int sc1, int sr2, int sc2);
	~Map();

	static Map* loadMap(int mapNum);
	void exportMap(int mapNum);

	void display();

	int getTileType(int x, int y);
	bool isValidTile(int x, int y);
	bool isValidSet(int x, int y, int tileType);

	void reverseTile(int x, int y);
	void setTile(int tilesInd, Tile* tile);
	bool setTile(int x, int y, int tileType);

	void setP1StartPosition(int x, int y);
	void setP2StartPosition(int x, int y);
	
	void testPlayerCollision( Player *p );
	void testProjectileCollision( Projectile *p );
	
	glm::vec3 getP1StartPos();
	glm::vec3 getP2StartPos();
	glm::vec3 getCenter(); // Get center position of map
	float getUnitWidth(); // Get width of map in GL units
	float getUnitHeight(); // Get height of map in GL units
};

#endif