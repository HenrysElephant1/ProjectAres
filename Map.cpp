#include "Map.h"

Map::Map() {

}

Map::~Map() {

}

void Map::display() {
	for( int i=0; i<x_size*y_size; i++ ) {
		tiles[i]->display();
	}
}