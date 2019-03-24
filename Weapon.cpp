#include "Weapon.h"

Weapon::Weapon() {

}

Weapon::~Weapon() {

}

void Weapon::display() {
	glPushMatrix();
	glTranslatef(offx,offy,offz);
	model->display();
	glPopMatrix();
}

void Weapon::update( float dt ) {
	timer -= dt;
	if( timer < 0 )
		timer = 0;
}

Projectile* Weapon::fire() {
	if( timer < .001 )
		return new Projectile(firex, firey, firez);
	else 
		return NULL;
}