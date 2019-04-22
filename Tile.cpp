#include "Tile.h"

Tile::Tile( int xPos, int yPos ) {
	x = xPos;
	y = yPos;

	hitbox_count=1;
	hitboxes = new Hitbox*[hitbox_count];
	for( int i=0; i<hitbox_count; i++ ) {
		hitboxes[i] = new Hitbox(TILE_SIZE, TILE_SIZE, glm::vec3(x*TILE_SIZE, 0, y*TILE_SIZE), 0);
	}
}

Tile::~Tile() {
	for( int i=0; i<hitbox_count; i++ ) {
		delete hitboxes[i];
	}
	delete[] hitboxes;
}

Tile* Tile::createTile(int x, int y, int tileType) {
	switch(tileType) {
		case FLOOR:
		default:
			return new FloorTile(x, y);
		case WALL:
			return new WallTile(x, y);
	}
}

void FloorTile::display() {

}

void WallTile::display() {
	for( int i=0; i<hitbox_count; i++ ) {
		hitboxes[i]->display();
	}
}