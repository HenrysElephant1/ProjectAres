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

bool Projectile::testHitboxIntersection( Hitbox* toTest, bool destroyOnContact, glm::vec3 *contactPos, glm::vec3 *contactVec ) {
	// If a contact pos is passed in, the user wants to know where it hit, so we can't test it as a point
	bool ret = (contactPos == NULL ? toTest->testPointHit( loc ) : false) || toTest->testVectorHit( prev, loc-prev, contactPos, contactVec );
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

void BasicProjectile::testMapHit( Hitbox *toTest ) {
	testHitboxIntersection( toTest, true );
}



ReboundProjectile::ReboundProjectile( glm::vec3 initLoc, float dir ): Projectile(initLoc) {
	vel = glm::vec3( Sin(dir) * REBOUND_PROJECTILE_SPEED, 0, Cos(dir) * REBOUND_PROJECTILE_SPEED );
	timer = 2;
}

ReboundProjectile::~ReboundProjectile() {}

void ReboundProjectile::display() {
	glPushMatrix();
	glTranslatef(loc.x, loc.y, loc.z);
	glColor3d(0,0,1);
	glBegin(GL_QUADS);
	glVertex3d( .2, .5, .2);
	glVertex3d( .2, .5,-.2);
	glVertex3d(-.2, .5,-.2);
	glVertex3d(-.2, .5, .2);
	glEnd();
	// model->display();
	glPopMatrix();
}

void ReboundProjectile::update( float dt ) {
	timer -= dt;
	destroy = timer <= 0;
	prev = loc;
	loc += vel * dt;
}

float ReboundProjectile::getDamage( bool contact, glm::vec3 pLoc ) { return (contact?10:0); }
bool ReboundProjectile::shouldTestPlayerHit() { return true; }

void ReboundProjectile::testMapHit( Hitbox *toTest ) {
	glm::vec3 contactPos, contactVec;
	bool collision = testHitboxIntersection( toTest, false, &contactPos, &contactVec );
	while( collision ) {
		prev = contactPos + contactVec * (float).01;
		loc = contactPos + contactVec;
		vel = glm::normalize( contactVec ) * (float)REBOUND_PROJECTILE_SPEED;
		collision = testHitboxIntersection( toTest, false, &contactPos, &contactVec );
	}
}
