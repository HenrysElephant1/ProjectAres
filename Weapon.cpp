#include "Weapon.h"

Weapon::Weapon( float ox, float oy, float oz, float fx, float fy, float fz ) {
	offx = ox;
	offy = oy;
	offz = oz;
	firex = fx;
	firey = fy;
	firez = fz;
}

Weapon::~Weapon() {

}

// void Weapon::display() {
// 	glPushMatrix();
// 	glTranslatef(offx,offy,offz);
// 	model->display();
// 	glPopMatrix();
// }

void Weapon::update( float dt ) {
	timer -= dt;
	if( timer < 0 )
		timer = 0;
}

void Weapon::getFireCoords( float x, float y, float z, float dir, float &retx, float &rety, float &retz ) {
	retx = x + Cos(dir) * (offx + firex) + Sin(dir) * (offz + firez);
	rety = y + offy + firey;
	retz = z + Cos(dir) * (offz + firez) - Sin(dir) * (offx + firex);
}

std::vector<Projectile*> Weapon::getProjectiles() {
	std::vector<Projectile*> toReturn = justFired;
	justFired.clear();
	return toReturn;
}



BasicWeapon::BasicWeapon( float ox, float oy, float oz ): Weapon(ox,oy,oz,0,0,4) {

}

BasicWeapon::~BasicWeapon() {

}

void BasicWeapon::fire( float x, float y, float z, float dir ) {
	float initx, inity, initz;
	getFireCoords(x, y, z, dir, initx, inity, initz);
	justFired.push_back( new BasicProjectile( initx, inity, initz, dir ) );
}

void BasicWeapon::display() {
	glPushMatrix();
	glTranslatef(offx,offy,offz);

	glBegin(GL_QUADS);
	glNormal3f(  0,  1,  0);
	glVertex3f(-.1, .5,  0);
	glVertex3f( .1, .5,  0);
	glVertex3f( .1, .5,  4);
	glVertex3f(-.1, .5,  4);
	glEnd();

	glPopMatrix();
}

void BasicWeapon::trigger( float x, float y, float z, float dir ) {
	if( !triggered ) fire(x,y,z,dir); // Single fire behavior
	triggered = true;
}

void BasicWeapon::release() {
	triggered = false;
}
