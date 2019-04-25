#include "Map.h"

Map::Map(std::string mName, int x, int y, int sr1, int sc1, int sr2, int sc2) {
	mapName = mName;
	x_size=x;
	y_size=y;
	p1StartRow = sr1;
	p1StartCol = sc1;
	p2StartRow = sr2;
	p2StartCol = sc2;
	tiles = new Tile*[x_size*y_size];

	for( int i=0; i<x_size*y_size; i++ ) {
		tiles[i] = NULL;
	}
}

Map::~Map() {
	for( int i=0; i<x_size*y_size; i++ ) {
		std::cout << "deleting tilenum " << i << std::endl;
		delete tiles[i];
	}
	delete[] tiles;
}

/**
 * Returns a saved map
 * */
Map* Map::loadMap(int mapNum) {
	std::string mapFilePath = mapFolder + "map" + std::to_string(mapNum) + ".txt";
	std::cout << mapFilePath << std::endl;
	std::ifstream mapFile {mapFilePath, std::ifstream::in};

	std::string mapName;
	int x_size, y_size, p1StartRow, p1StartCol, p2StartRow, p2StartCol;
	// parsing each token from the map file
	mapFile >> mapName;
	std::cout << mapName << std::endl;
	mapFile >> x_size;
	mapFile >> y_size;
	mapFile >> p1StartRow;
	mapFile >> p1StartCol;
	mapFile >> p2StartRow;
	mapFile >> p2StartCol;

	Map* loadedMap = new Map(mapName, x_size, y_size, p1StartRow, p1StartCol, p2StartRow, p2StartCol);
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

	mapFile << mapName << std::endl;
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

	// for Load Map, wanted grid-buttons with screenshots of the saved map
	exportMapScreenshot(mapNum);
}

void Map::exportMapScreenshot(int mapNum)
{
	int glWidth = this->getUnitWidth();
	int glHeight = this->getUnitHeight();
	
	// trying to save screenshot of map
	// BYTE* pixels = new BYTE[3 * width * height];

	// glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// // Convert to FreeImage format & save to file
	// FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0x0000FF, 0xFF0000, 0x00FF00, false);
	// FreeImage_Save(FIF_BMP, image, "maps/test.png", 0);

	// // Free resources
	// FreeImage_Unload(image);
	// delete [] pixels;
}

void Map::display() {
	for( int i=0; i<x_size*y_size; i++ ) {
		tiles[i]->display();
	}
}

std::string Map::getName() {
	return mapName;
}

Tile* Map::getTile(int x, int y) {
	return tiles[x + y*y_size];
}

void Map::setTile(int tileInd, Tile* tile) {
	// std::cout << "trying to delete " << tiles[tileInd]->getType() << std::endl;
	delete tiles[tileInd];
	
	tiles[tileInd] = tile;
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
