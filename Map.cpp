#include "Map.h"

Map::Map(int x, int y, int sr1, int sc1, int sr2, int sc2) {
	x_size=x;
	y_size=y;
	p1StartRow = sr1;
	p1StartCol = sc1;
	p2StartRow = sr2;
	p2StartCol = sc2;
	tiles = new Tile*[x_size*y_size];
	// int i = 0;
	// for( int row=-y_size/2; row<y_size/2; row++ ) {
	// 	for( int col=-x_size/2; col<y_size/2; col++ ) {
	// 		tiles[i++] = new Tile(col, row);
	// 	}
	// }
	// std::cout << "count " << i << std::endl;
}

Map::~Map() {
	for( int i=0; i<x_size*y_size; i++ ) {
		delete tiles[i];
	}
	delete[] tiles;
}

/**
 * Returns a saved map
 * */
Map* Map::loadMap(int mapNum) {
	std::string mapFilePath = "maps/map" + std::to_string(mapNum) + ".txt";
	std::ifstream mapFile {mapFilePath, std::ifstream::in};

	int x_size, y_size, p1StartRow, p1StartCol, p2StartRow, p2StartCol;
	// parsing each token from the map file
	mapFile >> x_size;
	mapFile >> y_size;
	mapFile >> p1StartRow;
	mapFile >> p1StartCol;
	mapFile >> p2StartRow;
	mapFile >> p2StartCol;

	Map* loadedMap = new Map(x_size, y_size, p1StartRow, p1StartCol, p2StartRow, p2StartCol);
	unsigned int tileType;
	int i = 0;
	for( int row=0; row<y_size; row++ ) {
		for( int col=0; col<x_size; col++ ) {
			mapFile >> tileType;
			loadedMap->setTile(i++, Tile::createTile(col, row, tileType));
		}
	}
	loadedMap->exportMap(9);
	return loadedMap;
}

void Map::exportMap(int mapNum) {
	std::string mapFilePath = "maps/map" + std::to_string(mapNum) + ".txt";
	std::ofstream mapFile(mapFilePath, std::ios_base::out);

	mapFile << x_size << " " << y_size << std::endl;
	mapFile << p1StartRow << " " << p1StartCol << std::endl;
	mapFile << p2StartRow << " " << p2StartCol << std::endl;

	int i = 0;
	for( int row=0; row<y_size; row++ ) {
		for( int col=0; col<x_size; col++ ) {
			mapFile << tiles[i++]->getType() << " ";
		}
		mapFile << std::endl;
	}
}

void Map::display() {
	for( int i=0; i<x_size*y_size; i++ ) {
		tiles[i]->display();
	}
}

Tile* Map::getTile(int x, int y) {
	return tiles[x + y*y_size];
}

void Map::setTile(int tilesInd, Tile* tile) {
	tiles[tilesInd] = tile;
}

void Map::testPlayerCollision( Player *p ){
	for( int i=0; i<x_size*y_size; i++ ) {
		tiles[i]->testPlayerCollision( p );
	}
}

void Map::testProjectileCollision( Projectile *p ){
	for( int i=0; i<x_size*y_size; i++ ) {
		tiles[i]->testProjectileCollision( p );
	}
}

glm::vec3 Map::getP1StartPos() {
	return glm::vec3(p1StartCol*TILE_SIZE, 0, p1StartRow*TILE_SIZE);
}

glm::vec3 Map::getP2StartPos() {
	return glm::vec3(p2StartCol*TILE_SIZE, 0, p2StartRow*TILE_SIZE);
}

glm::vec3 Map::getCenter() {
	return glm::vec3(((x_size-1)/2.0)*TILE_SIZE, 0, ((y_size-1)/2.0)*TILE_SIZE);
}
