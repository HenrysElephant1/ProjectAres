#include "Player.h"

Player::Player() {
	weapon1 = new BasicWeapon(glm::vec3(.3, 1, 1));
	weapon2 = new ReboundWeapon(glm::vec3(-.3, 1, 1));
	hitbox = new Hitbox(2,3.5);
	model = new Model(std::string("models/TestTank.fbx"));
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
	glColor3d(colr, colg, colb);
	glPushMatrix();
	glTranslatef(loc.x,loc.y,loc.z);
	glRotatef(dir,0,1,0);
	glPushMatrix();
	glScaled(.01,.01,.01);
	glRotated(90,0,1,0);
	model->display();
	glPopMatrix();

	weapon1->display();
	weapon2->display();

	glPopMatrix();

	hitbox->display();
}

void Player::update( float dt ) {
	turn(dt);
	move(dt);
	hitbox->update(loc, dir);
	weapon1->update(loc, dir, dt);
	weapon2->update(loc, dir, dt);
}

bool Player::testHit( Projectile* proj ) {
	bool contact = proj->testHitboxIntersection( hitbox, true );
	float damageDone = proj->getDamage( contact, loc );
	return contact;
}

void Player::testWorldCollision( Hitbox* toTest ) {
	if( testHitboxCollision( hitbox, toTest ) ) {
		loc = prevloc;
		dir = prevdir;
		update(0); // Update hitboxes and weapons but don't move or turn
	}
}

std::vector<Projectile*> Player::getProjectiles() {
	std::vector<Projectile*> toReturn;
	std::vector<Projectile*> w1Proj = weapon1->getProjectiles();
	std::vector<Projectile*> w2Proj = weapon2->getProjectiles();
	toReturn.insert( toReturn.begin(), w1Proj.begin(), w1Proj.end() );
	toReturn.insert( toReturn.begin(), w2Proj.begin(), w2Proj.end() );
	return toReturn;
}

void Player::setForward( bool newVal ) { forward = newVal; }
void Player::setBackward( bool newVal ) { backward = newVal; }
void Player::setLeft( bool newVal ) { left = newVal; }
void Player::setRight( bool newVal ) { right = newVal; }
void Player::triggerWeapon1() { weapon1->trigger(); }
void Player::triggerWeapon2() { weapon2->trigger(); }
void Player::releaseWeapon1() { weapon1->release(); }
void Player::releaseWeapon2() { weapon2->release(); }

void Player::setRGB( float r, float g, float b ) { colr = r; colg = g; colb = b; }
void Player::setHealth( int h ) { health = h; }
void Player::setSpeeds( float ms, float rs ) { moveSpeed = ms; rotationSpeed = rs; }

void Player::turn( float dt ) {
	prevdir = dir;
	int rotVal = left - right;
	dir += rotVal*rotationSpeed*dt;
	if(dir < 0) dir += 360;
	if(dir >= 360) dir -= 360;
}

void Player::move( float dt ) {
	prevloc = loc;
	int moveVal = forward - backward;
	loc.x += moveVal*Sin(dir)*moveSpeed*dt;
	loc.z += moveVal*Cos(dir)*moveSpeed*dt;
}

void Player::reset( glm::vec3 newLoc, float newDir ){ 
	loc = newLoc; 
	prevloc = newLoc;
	dir = newDir;
	prevdir = newDir;
	hitbox->update(loc, dir);
	weapon1->update(loc, dir, 0);
	weapon2->update(loc, dir, 0);
	alive = true;
}

Hitbox* Player::getHitbox() { return hitbox; }
