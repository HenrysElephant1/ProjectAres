#include "Projectile.h"

Projectile::Projectile( float x, float y, float z ) {
	locx = x;
	locy = y;
	locz = z;
}

Projectile::~Projectile() {

}

void Projectile::display() {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(locx, locy, locz);
	model->display();
	glPopMatrix();
}

void Projectile::update( float dt ) {
	timer -= dt;
	if( timer < 0 )
		timer = 0;
}