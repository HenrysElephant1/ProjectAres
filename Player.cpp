#include "Player.h"

Player::Player() {
	weapon1 = new BasicWeapon(.3, .5, 0);
	weapon2 = new BasicWeapon(-.3, .5, 0);
	hitbox = new Hitbox(2,4);
	model = new Model();
	moveSpeed = 20;
	rotationSpeed = 180;
}

Player::~Player() {
	delete weapon1;
	delete weapon2;
	delete hitbox;
	delete model;
}

void Player::display() {
	glPushMatrix();
	glTranslatef(locx,0,locz);
	glRotatef(dir,0,1,0);
	model->display();

	glColor3d(colr, colg, colb);
	glBegin(GL_QUADS);
	glNormal3f(  0, -1,  0);
	glVertex3f( -1,  0, -2);
	glVertex3f(  1,  0, -2);
	glVertex3f(  1,  0,  2);
	glVertex3f( -1,  0,  2);

	glNormal3f(  0,  1,  0);
	glVertex3f( -1, .5, -2);
	glVertex3f(  1, .5, -2);
	glVertex3f(  1, .5,  2);
	glVertex3f( -1, .5,  2);

	glNormal3f(  0,  0, -1);
	glVertex3f( -1, .5, -2);
	glVertex3f(  1, .5, -2);
	glVertex3f(  1,  0, -2);
	glVertex3f( -1,  0, -2);

	glNormal3f(  0,  0,  1);
	glVertex3f( -1, .5,  2);
	glVertex3f(  1, .5,  2);
	glVertex3f(  1,  0,  2);
	glVertex3f( -1,  0,  2);

	glNormal3f( -1,  0,  0);
	glVertex3f( -1, .5, -2);
	glVertex3f( -1, .5,  2);
	glVertex3f( -1,  0,  2);
	glVertex3f( -1,  0, -2);

	glNormal3f(  1,  0,  0);
	glVertex3f(  1, .5, -2);
	glVertex3f(  1, .5,  2);
	glVertex3f(  1,  0,  2);
	glVertex3f(  1,  0, -2);
	glEnd();

	weapon1->display();
	weapon2->display();
	
	glPopMatrix();
}

void Player::update( float dt, std::vector<Projectile*> ) {
	turn(dt);
	move(dt);
	hitbox->update(locx, locz, dir);
}

Projectile* Player::fireWeapon1() { return weapon1->fire(locx,0,locz,dir); }
Projectile* Player::fireWeapon2() { return weapon2->fire(locx,0,locz,dir); }

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
	locx += moveVal*Sin(dir)*moveSpeed*dt;
	locz += moveVal*Cos(dir)*moveSpeed*dt;
}

void Player::reset( float newX, float newZ, float newDir ){ 
	locx = newX;
	locz = newZ;
	dir = newDir;
	alive = true;
}
