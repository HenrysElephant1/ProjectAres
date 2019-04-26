#include "Map.h"

Map::Map(int x, int y, int sr1, int sc1, int sr2, int sc2) {
	x_size=x;
	y_size=y;
	p1StartRow = sr1;
	p1StartCol = sc1;
	p2StartRow = sr2;
	p2StartCol = sc2;

	tiles = new Tile*[x_size*y_size];
	int i = 0;
	for( int row=0; row<y_size; row++ ) {
		for( int col=0; col<x_size; col++ ) {
			tiles[i++] = Tile::createTile(col, row, Tile::FLOOR);
		}
	}
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
	std::string mapFilePath = mapFolder + "map" + std::to_string(mapNum) + ".txt";
	std::cout << "Loading in " << mapFilePath << std::endl;
	std::ifstream mapFile {mapFilePath, std::ifstream::in};
	
	if (!mapFile) {
		std::cout << "Map read failed" << std::endl;
		std::cerr << "Error: " << strerror(errno) << std::endl;
		// Default map in case read fails
		return new Map(10, 10, 1, 1, 8, 8);
	}

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
	
	return loadedMap;
}


void Map::exportMap(int mapNum) {
	std::string mapFilePath = mapFolder + "map" + std::to_string(mapNum) + ".txt";
	// ios_base::out makes current map overwrite any pre-existing map in "map[mapNum].txt"
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

/**
 * Returns true if coordinates are outside map, including the outer walls
 * */
bool Map::isOutOfBounds(int x, int y) {
	return x <= 0 || x >= x_size -1 || y <= 0 || y >= y_size - 1;
}

Tile* Map::getTile(int x, int y) {
	if( x < 0 || x >= x_size || y < 0 || y >= y_size ) {
		return NULL;
	}
	return tiles[x + y*x_size];
}

void Map::setTile(int tileInd, Tile* tile) {
	delete tiles[tileInd];
	
	tiles[tileInd] = tile;
}

bool Map::setTile(int x, int y, int tileType) {
	// Checking bounds and restricting changing tile-borders, which should remain walls
	if( isOutOfBounds(x, y) ) {
		return false;
	}

	int tileInd = y*x_size + x;

	setTile(tileInd, Tile::createTile(x, y, tileType));
	return true;
}

void Map::setP1StartPosition(int x, int y) {
	if( setTile(x, y, Tile::FLOOR) ) {
		p1StartCol = x;
		p1StartRow = y;
	}
}

void Map::setP2StartPosition(int x, int y) {
	if( setTile(x, y, Tile::FLOOR) ) {
		p2StartCol = x;
		p2StartRow = y;
	}
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

float Map::getUnitWidth() {
	return x_size * TILE_SIZE;
}

float Map::getUnitHeight() {
	return y_size * TILE_SIZE;
}
