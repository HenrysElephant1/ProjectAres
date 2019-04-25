#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "GLManager.h"
#include "Hitbox.h"
#include "Weapon.h"
#include "Projectile.h"

#define MAX_HEALTH 100.0

static std::string healthBarTexName = "textures/oil.png";

class Player {
private:
	// Player attributes
	float health;
	float moveSpeed, rotationSpeed;
	float colr, colg, colb;
	Weapon *weapon1, *weapon2;
	Hitbox *hitbox;
	Model *model;

	// Player location and direction in degrees (0deg is vector j or {0,1})
	glm::vec3 loc, prevloc;
	float dir, prevdir;

	// Player control booleans
	bool forward = false, backward = false, left = false, right = false;

	// For flashing red on hit
	float hitTimer;
	
	// Called in update
	void turn( float dt );
	void move( float dt );

	static GLuint healthBarTex;

public:
	Player();
	~Player();

	// Game loop functions
	void display();
	void displayHealthBar( bool flipHorizontal );
	void update( float dt );
	void testHit( Projectile* proj ); // Test projectile hit and decrease health if necessary 
	void testWorldCollision( Hitbox *toTest ); // Test collision with a world hitbox and don't move if collided
	std::vector<Projectile*> getProjectiles();

	// Contols
	void setForward( bool newVal );
	void setBackward( bool newVal );
	void setLeft( bool newVal );
	void setRight( bool newVal );
	void triggerWeapon1();
	void triggerWeapon2();
	void releaseWeapon1();
	void releaseWeapon2();

	// Setters for player customization in menus
	void setRGB( float r, float g, float b );
	void setHealth( int h );
	void setSpeeds( float ms, float rs );

	// Reset on new game
	void reset( glm::vec3 newLoc, float newDir );

	// Accessors
	Hitbox* getHitbox();
	float getHealth();
};

#endif