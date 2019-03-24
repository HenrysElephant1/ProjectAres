#include "Player.h"

Player::Player() {
	weapon1 = new Weapon();
	weapon2 = new Weapon();
	hitbox = new Hitbox(1,1);
	model = new Model();
}

Player::~Player() {
	delete weapon1;
	delete weapon2;
	delete hitbox;
	delete model;
}

void Player::display() {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(locx,locy,0);
	glRotatef(dir,0,1,0);
	model->display();
	weapon1->display();
	weapon2->display();
	glPopMatrix();
}

void Player::update( float dt, std::vector<Projectile*> ) {
	turn(dt);
	move(dt);
	hitbox->update(locx, locy, dir);
}

Projectile* Player::fireWeapon1() { return weapon1->fire(); }
Projectile* Player::fireWeapon2() { return weapon2->fire(); }

void Player::setForward( bool newVal ) { forward = newVal; }
void Player::setBackward( bool newVal ) { backward = newVal; }
void Player::setLeft( bool newVal ) { left = newVal; }
void Player::setRight( bool newVal ) { right = newVal; }

void Player::setRGB( float r, float g, float b ) { colr = r; colg = g; colb = b; }
void Player::setHealth( int h ) { health = h; }
void Player::setSpeeds( float ms, float rs ) { moveSpeed = ms; rotationSpeed = rs; }

void Player::turn( float dt ) {
	int rotVal = left - right;
	dir += rotVal*rotationSpeed*dt;
	if(dir < 0) dir += 360;
	if(dir >= 360) dir -= 360;
}

void Player::move( float dt ) {
	int moveVal = forward - backward;
	locx += moveVal*Cos(dir)*moveSpeed*dt;
	locy += moveVal*Sin(dir)*moveSpeed*dt;
}

void Player::reset( float newX, float newY, float newDir ){ 
	locx = newX;
	locy = newY;
	dir = newDir;
	alive = true;
}
