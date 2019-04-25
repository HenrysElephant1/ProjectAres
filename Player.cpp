#include "Player.h"

GLuint Player::healthBarTex = 0;

Player::Player() {
	health = 100.0;
	weapon1 = new BasicWeapon(glm::vec3(.3, 1, 1));
	weapon2 = new ReboundWeapon(glm::vec3(-.3, 1, 1));
	hitbox = new Hitbox(2,3.5);
	model = new Model(std::string("models/AresTankBase.fbx"));
	moveSpeed = 20;
	rotationSpeed = 180;
	healthBarTex = GLManager::loadTexture(healthBarTexName);
}

Player::~Player() {
	delete weapon1;
	delete weapon2;
	delete hitbox;
	delete model;
}

void Player::display() {
	if( health > 0 ) {
		float shininess[] = {32.0f};
		float spec_color[] = {1.0,1.0,1.0,1.0};
		glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, spec_color );

		if( hitTimer > 0 ) { glColor3d(1.0,0.4,0.4); /*glUseProgram(0);*/ }
		else glColor3d(colr, colg, colb);
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

		// if( hitTimer > 0 ) { glUseProgram(GLManager::lightingShader); }

	}
}

void Player::displayHealthBar( bool flipHorizontal ) {
	GLManager::switchTo2D();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, healthBarTex);
	glPushMatrix();
	if( flipHorizontal ) glScaled(-1,1,1);
	float healthBarCoord = health / MAX_HEALTH * .8 + .05;
	glColor3d(colr,colg,colb);
	glBegin(GL_QUADS);
	glTexCoord2f(health/MAX_HEALTH,1); glVertex2d(healthBarCoord,.95);
	glTexCoord2f(0,1); glVertex2d(.05,.95);
	glTexCoord2f(0,0); glVertex2d(.05,.85);
	glTexCoord2f(health/MAX_HEALTH,0); glVertex2d(healthBarCoord,.85);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	GLManager::switchTo3D();

	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	gluLookAt(0,10,10, 0,0,0, 0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	if( flipHorizontal ) glScaled(-1,1,1);

	GLManager::doLighting(5.2,10,0);
	glTranslatef(5.1,6.2,0);
	glRotatef(35,0,1,0);
	glScalef(.003,.003,.003);
	model->display();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	//Now display Tank
}

void Player::update( float dt ) {
	turn(dt);
	move(dt);
	hitbox->update(loc, dir);
	weapon1->update(loc, dir, dt);
	weapon2->update(loc, dir, dt);
	if( health <= 0 ) {
		weapon1->release();
		weapon2->release();
	}
	hitTimer -= dt;
	if( hitTimer < 0 ) hitTimer = 0;
}

void Player::testHit( Projectile* proj ) {
	if( health > 0 ) {
		bool contact = proj->testHitboxIntersection( hitbox, true );
		float damageDone = proj->getDamage( contact, loc );
		health -= damageDone;
		if( damageDone > 0 )
			hitTimer = 0.1;
	}
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
	if( health > 0 ) {
		std::vector<Projectile*> w1Proj = weapon1->getProjectiles();
		std::vector<Projectile*> w2Proj = weapon2->getProjectiles();
		toReturn.insert( toReturn.begin(), w1Proj.begin(), w1Proj.end() );
		toReturn.insert( toReturn.begin(), w2Proj.begin(), w2Proj.end() );
	}
	return toReturn;
}

void Player::setForward( bool newVal ) { forward = newVal; }
void Player::setBackward( bool newVal ) { backward = newVal; }
void Player::setLeft( bool newVal ) { left = newVal; }
void Player::setRight( bool newVal ) { right = newVal; }
void Player::triggerWeapon1() { if(health > 0) weapon1->trigger(); }
void Player::triggerWeapon2() { if(health > 0) weapon2->trigger(); }
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
	health = MAX_HEALTH;
	loc = newLoc; 
	prevloc = newLoc;
	dir = newDir;
	prevdir = newDir;
	hitbox->update(loc, dir);
	weapon1->update(loc, dir, 0);
	weapon2->update(loc, dir, 0);
	forward = false;
	backward = false;
	left = false;
	right = false;
	hitTimer = 0;
}

Hitbox* Player::getHitbox() { return hitbox; }
float Player::getHealth() { return health; }
