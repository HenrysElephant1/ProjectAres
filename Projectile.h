#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Model.h"
#include "GLManager.h"
#include "Hitbox.h"

#define BASIC_PROJECTILE_SPEED 40

class Projectile {
protected:
	Model* model;
	float timer;
	glm::vec3 loc, prev;

	bool destroy = false;

public:
	Projectile( glm::vec3 initLoc );
	virtual ~Projectile();

	virtual void display() = 0;
	virtual void update( float dt ) = 0; 
	virtual float getDamage( bool contact, glm::vec3 pLoc ) = 0; // Get numerical damage of projectile based on proximity
	virtual bool shouldTestPlayerHit() = 0; // Should the projectile be tested for player hits (maybe not if an explosion weapon)
	
	bool testHitboxIntersection( Hitbox* toTest, bool destroyOnContact ); // Test vector intersection from prev to loc with hitbox. Can be overriden
	bool shouldDestroy(); // Should the projectile be deleted?
};


class BasicProjectile: public Projectile {
private:
	glm::vec3 vel; // Velocity of projectile

public:
	BasicProjectile( glm::vec3 initLoc, float dir );
	~BasicProjectile();

	// Inherited methods
	void display();
	void update( float dt );
	float getDamage( bool contact, glm::vec3 pLoc );
	bool shouldTestPlayerHit(); 
};

#endif