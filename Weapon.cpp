#include "Weapon.h"

Weapon::Weapon( glm::vec3 base, glm::vec3 fire ) {
	baseOffset = base;
	fireOffset = fire;
}

Weapon::~Weapon() {

}

// void Weapon::display() {
// 	glPushMatrix();
// 	glTranslatef(baseOffset.x,baseOffset.y,baseOffset.z);
// 	model->display();
// 	glPopMatrix();
// }

void Weapon::update( glm::vec3 newLoc, float newDir, float dt ) {
	loc = newLoc;
	dir = newDir;
	timer -= dt;
	if( timer < 0 )
		timer = 0;
}

glm::vec3 Weapon::getFireCoords() {
	return glm::vec3(
		loc.x + Cos(dir) * (baseOffset.x + fireOffset.x) + Sin(dir) * (baseOffset.z + fireOffset.z),
		loc.y + baseOffset.y + fireOffset.y,
		loc.z + Cos(dir) * (baseOffset.z + fireOffset.z) - Sin(dir) * (baseOffset.x + fireOffset.x)
	);
}

std::vector<Projectile*> Weapon::getProjectiles() {
	std::vector<Projectile*> toReturn = justFired;
	justFired.clear();
	return toReturn;
}



BasicWeapon::BasicWeapon( glm::vec3 offset ): Weapon(offset,glm::vec3(0,0,4)) {}
BasicWeapon::~BasicWeapon() {}

void BasicWeapon::display() {
	glPushMatrix();
	glTranslatef(baseOffset.x,baseOffset.y,baseOffset.z);

	glBegin(GL_QUADS);
	glNormal3f(  0,  1,  0);
	glVertex3f(-.1, .5,  0);
	glVertex3f( .1, .5,  0);
	glVertex3f( .1, .5,  4);
	glVertex3f(-.1, .5,  4);
	glEnd();

	glPopMatrix();
}

void BasicWeapon::trigger() {
	if( !triggered ) justFired.push_back( new BasicProjectile( getFireCoords(), dir ) ); // Single fire behavior
	triggered = true;
}

void BasicWeapon::release() {
	triggered = false;
}



ReboundWeapon::ReboundWeapon( glm::vec3 offset ): Weapon(offset,glm::vec3(0,0,4)) {}
ReboundWeapon::~ReboundWeapon() {}

void ReboundWeapon::display() {
	glPushMatrix();
	glTranslatef(baseOffset.x,baseOffset.y,baseOffset.z);

	glBegin(GL_TRIANGLES);
	glNormal3f(  0,  1,  0);
	glVertex3f(-.1, .5,  0);
	glVertex3f( .1, .5,  0);
	glVertex3f(  0, .5,  4);
	glEnd();

	glPopMatrix();
}

void ReboundWeapon::trigger() {
	if( !triggered ) justFired.push_back( new ReboundProjectile( getFireCoords(), dir ) ); // Single fire behavior
	triggered = true;
}

void ReboundWeapon::release() {
	triggered = false;
}
