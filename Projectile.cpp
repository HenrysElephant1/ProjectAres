#include "Projectile.h"

Projectile::Projectile( glm::vec3 initLoc ) {
	loc = initLoc;
	prev = initLoc;
}

Projectile::~Projectile() {

}

bool Projectile::shouldDestroy() {
	return destroy;
}

bool Projectile::testHitboxIntersection( Hitbox* toTest, bool destroyOnContact ) {
	bool ret = toTest->testVectorHit( prev, loc-prev );
	if( ret && destroyOnContact ) destroy = true;
	return ret;
}

BasicProjectile::BasicProjectile( glm::vec3 initLoc, float dir ): Projectile(initLoc) {
	vel = glm::vec3( Sin(dir) * BASIC_PROJECTILE_SPEED, 0, Cos(dir) * BASIC_PROJECTILE_SPEED );
	timer = 2;
}

BasicProjectile::~BasicProjectile() {}

void BasicProjectile::display() {
	glPushMatrix();
	glTranslatef(loc.x, loc.y, loc.z);
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
	destroy = timer <= 0;
	prev = loc;
	loc += vel * dt;
}

float BasicProjectile::getDamage( bool contact, glm::vec3 pLoc ) { return (contact?10:0); }
bool BasicProjectile::shouldTestPlayerHit() { return true; }
