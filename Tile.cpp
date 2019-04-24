#include "Tile.h"

std::string Tile::floorTex = "textures/gravel.png";

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

int FloorTile::getType() {
	return FLOOR;
}

void FloorTile::display() {
	GLuint tex = GLManager::loadTexture(floorTex);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUseProgram(GLManager::lightingShader);

	glPushMatrix();
	glTranslated(x*TILE_SIZE,0,y*TILE_SIZE);
	glScaled(TILE_SIZE,1,TILE_SIZE);
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glColor3f(1.0,1.0,1.0);
	glTexCoord2f(0,0); glVertex3f(-.5, 0,-.5);
	glTexCoord2f(0,1); glVertex3f(-.5, 0, .5);
	glTexCoord2f(1,1); glVertex3f( .5, 0, .5);
	glTexCoord2f(1,0); glVertex3f( .5, 0,-.5);
	glEnd();
	glPopMatrix();

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

WallTile::WallTile( int x, int y ) : Tile(x, y) {
	hitbox_count=1;
	hitboxes = new Hitbox*[hitbox_count];
	for( int i=0; i<hitbox_count; i++ ) {
		hitboxes[i] = new Hitbox(TILE_SIZE, TILE_SIZE, glm::vec3(x*TILE_SIZE, 0, y*TILE_SIZE), 0);
	}
}

int WallTile::getType() {
	return WALL;
}

void WallTile::display() {
	for( int i=0; i<hitbox_count; i++ ) {
		hitboxes[i]->display();
	}
}
