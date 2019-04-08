#include "Projectile.h"

Projectile::Projectile( float x, float y, float z ) {
	locx = x;
	locy = y;
	locz = z;
	prevx = x;
	prevy = y;
	prevz = z;
}

Projectile::~Projectile() {

}

bool Projectile::destroy() {
	return timer <= 0;
}

bool Projectile::testHit( Hitbox* toTest ) {
	glm::vec3 bVec = glm::vec3(prevx, prevy, prevz);
	glm::vec3 mVec = glm::vec3(locx, locy, locz) - bVec;
	return toTest->testVectorHit( bVec, mVec );
}

BasicProjectile::BasicProjectile( float x, float y, float z, float dir ): Projectile(x,y,z) {
	velx = Sin(dir) * BASIC_PROJECTILE_SPEED;
	velz = Cos(dir) * BASIC_PROJECTILE_SPEED;
	timer = 2;
}

BasicProjectile::~BasicProjectile() {}

void BasicProjectile::display() {
	glPushMatrix();
	glTranslatef(locx, locy, locz);
	glColor3d(1,0,0);
	glBegin(GL_QUADS);
	glVertex3d( .2, .5, .2);
	glVertex3d( .2, .5,-.2);
	glVertex3d(-.2, .5,-.2);
	glVertex3d(-.2, .5, .2);
	glEnd();
	// model->display();
	glPopMatrix();
}

void BasicProjectile::update( float dt ) {
	timer -= dt;
	prevx = locx;
	prevy = locy;
	prevz = locz;
	locx += velx * dt;
	locz += velz * dt;
}

float BasicProjectile::getDamage( float prox ) { return 10; }
bool BasicProjectile::testPlayerHit() { return true;}
