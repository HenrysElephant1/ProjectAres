#include "Tile.h"

Tile::Tile( int xPos, int yPos ) {
	x = xPos;
	y = yPos;
}

Tile::~Tile() {
	for( int i=0; i<hitbox_count; i++ ) {
		delete hitboxes[i];
	}
	delete[] hitboxes;
}

void Tile::testPlayerCollision( Player *p ){
	for( int i=0; i<hitbox_count; i++ ) {
		p->testWorldCollision( hitboxes[i] );
	}
}

void Tile::testProjectileCollision( Projectile *p ){
	for( int i=0; i<hitbox_count; i++ ) {
		p->testMapHit( hitboxes[i] );
	}
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

FloorTile::FloorTile( int x, int y ) : Tile(x, y) {
	hitbox_count = 0;
}

void FloorTile::display() {

}

WallTile::WallTile( int x, int y ) : Tile(x, y) {
	hitbox_count=1;
	hitboxes = new Hitbox*[hitbox_count];
	for( int i=0; i<hitbox_count; i++ ) {
		hitboxes[i] = new Hitbox(TILE_SIZE, TILE_SIZE, glm::vec3(x*TILE_SIZE, 0, y*TILE_SIZE), 0);
	}
}

void WallTile::display() {
	for( int i=0; i<hitbox_count; i++ ) {
		hitboxes[i]->display();
	}
}
