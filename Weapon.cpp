#include "Weapon.h"

Weapon::Weapon( glm::vec3 base, glm::vec3 fire ) {
	baseOffset = base;
	fireOffset = fire;
	triggered = false;
}

Weapon::~Weapon() {

}

void Weapon::display() {
	glPushMatrix();
	glTranslatef(baseOffset.x,baseOffset.y,baseOffset.z);
	glRotated(-90,0,1,0);
	glScaled(.01,.01,.01);
	// glColor3d(0,0,1);
	model->display();
	glPopMatrix();
}

void Weapon::update( glm::vec3 newLoc, float newDir, float dt ) {
	loc = newLoc;
	dir = newDir;
	timer -= dt;
	if( timer < 0 )
		timer = 0;
	updateSub(dt);
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



BasicWeapon::BasicWeapon( glm::vec3 offset ): Weapon(offset,glm::vec3(0,.2,1.5)) {
	model = new Model(std::string("models/TestWeapon.fbx"));
}
BasicWeapon::~BasicWeapon() {}

void BasicWeapon::trigger() {
	if( !triggered ) justFired.push_back( new BasicProjectile( getFireCoords(), dir ) ); // Single fire behavior
	triggered = true;
}

void BasicWeapon::release() {
	triggered = false;
}

void BasicWeapon::updateSub( float dt ) {}


ReboundWeapon::ReboundWeapon( glm::vec3 offset ): Weapon(offset,glm::vec3(0,.2,1.5)) {
	model = new Model(std::string("models/TestWeapon.fbx"));
}
ReboundWeapon::~ReboundWeapon() {}

void ReboundWeapon::trigger() {
	if( !triggered ) justFired.push_back( new ReboundProjectile( getFireCoords(), dir ) ); // Single fire behavior
	triggered = true;
}

void ReboundWeapon::release() {
	triggered = false;
}

void ReboundWeapon::updateSub( float dt ) {}



RapidFireWeapon::RapidFireWeapon( glm::vec3 offset ): Weapon(offset,glm::vec3(0,.2,1.5)) {
	model = new Model(std::string("models/TestWeapon.fbx"));
}
RapidFireWeapon::~RapidFireWeapon() {}

void RapidFireWeapon::trigger() {
	if( !overheated ) triggered = true;
}

void RapidFireWeapon::release() {
	triggered = false;
	lastFireTime = 0;
}

void RapidFireWeapon::updateSub( float dt ) {
	if( triggered ) {
		float timeLeft = dt + lastFireTime;
		while( timeLeft > 0 ) {
			glm::vec3 timeOffset = timeLeft * glm::vec3( Sin(dir) * RAPIDFIRE_PROJECTILE_SPEED, 0, Cos(dir) * RAPIDFIRE_PROJECTILE_SPEED );
			justFired.push_back( new RapidFireProjectile( getFireCoords() + timeOffset, dir ) );
			timeLeft -= 1.0 / RAPIDFIRE_RATE;
		}
		lastFireTime = timeLeft;
	}
	if( overheated ) {
		timer -= dt;
		if( timer <= 0 )
			overheated = false;
	}
	else {
		if( triggered )
			timer += dt;
		else
			timer -= dt;
		if( timer > 3.0 ) {
			triggered = false;
			overheated = true;
		}
	}
}
