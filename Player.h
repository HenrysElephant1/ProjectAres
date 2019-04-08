#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "GLManager.h"
#include "Hitbox.h"
#include "Weapon.h"
#include "Projectile.h"

class Player {
private:
	// Player attributes
	int health;
	float moveSpeed, rotationSpeed;
	float colr, colg, colb;
	Weapon *weapon1, *weapon2;
	Hitbox *hitbox;
	Model *model;
	bool alive = true;

	// Player location and direction in degrees (0deg is vector j or {0,1})
	float locx, locz, dir;

	// Player control booleans
	bool forward = false, backward = false, left = false, right = false;
	
	// Called in update
	void turn( float dt );
	void move( float dt );
	bool testHit( Projectile* proj );

public:
	Player();
	~Player();

	// Game loop functions
	void display();
	void update( float dt );
	void triggerWeapon1();
	void triggerWeapon2();
	void releaseWeapon1();
	void releaseWeapon2();
	std::vector<Projectile*> getProjectiles();

	// Contols
	void setForward( bool newVal );
	void setBackward( bool newVal );
	void setLeft( bool newVal );
	void setRight( bool newVal );

	// Setters for player customization in menus
	void setRGB( float r, float g, float b );
	void setHealth( int h );
	void setSpeeds( float ms, float rs );

	// Reset on new game
	void reset( float newX, float newZ, float newDir );

	// Accessors
	Hitbox* getHitbox();
};

#endif