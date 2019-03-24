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

	// Player location and direction in degrees (0deg is vector i or {1,0})
	float locx, locy, dir;

	// Player control booleans
	bool forward, backward, left, right;
	
	// Called in update
	void turn( float dt );
	void move( float dt );
	void testHit(std::vector<Projectile*>);

public:
	Player();
	~Player();

	// Game loop functions
	void display();
	void update( float dt, std::vector<Projectile*> );
	Projectile* fireWeapon1();
	Projectile* fireWeapon2();

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
	void reset( float newX, float newY, float newDir );
};

#endif