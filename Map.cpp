#include "Map.h"

Map::Map(int x, int y) {
	x_size=x;
	y_size=y;
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

	unsigned int x_size, y_size;
	unsigned int p1StartTileInd, p2StartTileInd;

	mapFile >> x_size;
	mapFile >> y_size;
	mapFile >> p1StartTileInd;
	mapFile >> p2StartTileInd;

	Map* loadedMap = new Map(x_size, y_size);
	unsigned int tileType;
	int i = 0;
	for( int row=-y_size/2; row<y_size/2; row++ ) {
		for( int col=-x_size/2; col<x_size/2; col++ ) {
			mapFile >> tileType;
			loadedMap->setTile(i++, Tile::createTile(col, row, tileType));
		}
	}
	
	return loadedMap;
}

void Map::display() {
	for( int i=0; i<x_size*y_size; i++ ) {
		tiles[i]->display();
	}
}

Tile* Map::getTile(int x, int y) {
	return tiles[x*x_size + y*y_size];
}

void Map::setTile(int tilesInd, Tile* tile) {
	tiles[tilesInd] = tile;
}