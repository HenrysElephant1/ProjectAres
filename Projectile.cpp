#include "Projectile.h"

Projectile::Projectile( float x, float y, float z ) {
	locx = x;
	locy = y;
	locz = z;
}

Projectile::~Projectile() {

}

bool Projectile::destroy() {
	return timer <= 0;
}

BasicProjectile::BasicProjectile( float x, float y, float z, float dir ): Projectile(x,y,z) {
	velx += Sin(dir) * BASIC_PROJECTILE_SPEED;
	velz += Cos(dir) * BASIC_PROJECTILE_SPEED;
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
	locx += velx * dt;
	locz += velz * dt;
}