#include "Tile.h"

std::string Tile::floorTex = "textures/gravel.png";
std::string Tile::wallTex = "textures/wall.png";


Tile::Tile( int xPos, int yPos ) {
	x = xPos;
	y = yPos;
}

void FloorTile::testPlayerCollision( Player *p ){
	for( int i=0; i<hitbox_count; i++ ) {
		p->testWorldCollision( hitboxes[i] );
	}
}

void FloorTile::testProjectileCollision( Projectile *p ){
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
			return new WallTile(x,y, WallTile::CENTER, new FloorTile(x, y));
	}
}

FloorTile::FloorTile( int x, int y ) : Tile(x, y) {
	hitbox_count = 0;
}

FloorTile::~FloorTile() {
	for( int i=0; i<hitbox_count; i++ ) {
		delete hitboxes[i];
	}
}

int FloorTile::getType() {
	return FLOOR;
}

void FloorTile::display() {
	float shininess[] = {0.0f};
	float spec_color[] = {0.0,0.0,0.0,1.0};

	GLuint tex = GLManager::loadTexture(floorTex);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUseProgram(GLManager::lightingShader);

	glColor3f(1.0,1.0,1.0);
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, spec_color );
	glPushMatrix();
	glTranslated(x*TILE_SIZE,0,y*TILE_SIZE);
	glScaled(TILE_SIZE,1,TILE_SIZE);
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(0,1); glVertex3f(-.5, 0,-.5);
	glTexCoord2f(0,0); glVertex3f(-.5, 0, .5);
	glTexCoord2f(1,0); glVertex3f( .5, 0, .5);
	glTexCoord2f(1,1); glVertex3f( .5, 0,-.5);
	glEnd();
	glPopMatrix();

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

WallTile::WallTile( int x, int y, int wallType, Tile *p) : TileDecorator(x, y, p) {
	hitbox_count=1;
	hitboxes = new Hitbox*[hitbox_count];
	for( int i=0; i<hitbox_count; i++ ) {
		
		switch(wallType)
		{
			case RIGHT:
				xOffset = TILE_SIZE/3;
				yOffset = 0;
				break;
			case TOP:
				xOffset = 0;
				yOffset = TILE_SIZE/3;
				break;
			case BOTTOM:
				xOffset = 0;
				yOffset = -TILE_SIZE/3;
				break;
			case LEFT:
				xOffset = -TILE_SIZE/3;
				yOffset = 0;
				break;
			default:
				break;
		}
		hitboxes[i] = new Hitbox(TILE_SIZE/2, TILE_SIZE/2, glm::vec3(x*TILE_SIZE + xOffset, 0, y*TILE_SIZE + yOffset), 0);
	}
}

WallTile::~WallTile() {
	for( int i=0; i<hitbox_count; i++ ) {
		delete hitboxes[i];
	}
	//delete parent;
}

int WallTile::getType() {
	return WALL;
}

void WallTile::display() {
	for( int i=0; i<hitbox_count; i++ ) {
		//hitboxes[i]->display();
	}
	float shininess[] = {0.0f};
	float spec_color[] = {0.0,0.0,0.0,1.0};

	GLuint tex = GLManager::loadTexture(wallTex);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUseProgram(GLManager::lightingShader);

	glColor3f(1.0,1.0,1.0);
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, spec_color );
	glPushMatrix();
	glTranslated(x*TILE_SIZE + xOffset,0,y*TILE_SIZE + yOffset);
	glScaled(TILE_SIZE/2,1,TILE_SIZE/2);
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(0,1); glVertex3f(-.5, 0,-.5);
	glTexCoord2f(0,0); glVertex3f(-.5, 0, .5);
	glTexCoord2f(1,0); glVertex3f( .5, 0, .5);
	glTexCoord2f(1,1); glVertex3f( .5, 0,-.5);
	glEnd();
	glPopMatrix();

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	parent->display();
}

TileDecorator::TileDecorator(int x, int y, Tile * t) : Tile(x,y)
{
	parent = t;
}

TileDecorator::~TileDecorator()
{
	delete parent;
}

void TileDecorator::testPlayerCollision( Player *p ){
	for( int i=0; i<hitbox_count; i++ ) {
		p->testWorldCollision( hitboxes[i] );
	}
	parent->testPlayerCollision(p);

}

void TileDecorator::testProjectileCollision( Projectile *p ){
	for( int i=0; i<hitbox_count; i++ ) {
		p->testMapHit( hitboxes[i] );
	}
	parent->testProjectileCollision(p);
}
