#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Model.h"
#include "GLManager.h"
#include "Hitbox.h"

#define BASIC_PROJECTILE_SPEED 40;

class Projectile {
protected:
	Model* model;
	float timer;
	float locx, locy, locz, prevx, prevy, prevz;

public:
	Projectile( float x, float y, float z );
	virtual ~Projectile();

	virtual void display() = 0;
	virtual void update( float dt ) = 0; 
	virtual float getDamage( float prox ) = 0;       // Get numerical damage of projectile based on proximity
	virtual bool testPlayerHit() = 0;                // Should the projectile be tested for player hits (maybe not if an explosion weapon)
	
	bool testHit( Hitbox* toTest );  				 // Test vector intersection from prev to loc with hitbox
	bool destroy();									 // Should the projectile be deleted?
};


class BasicProjectile: public Projectile {
private:
	float velx, velz;

public:
	BasicProjectile( float x, float y, float z, float dir );
	~BasicProjectile();

	// Inherited methods
	void display();
	void update( float dt );
	float getDamage( float prox );
	bool testPlayerHit(); 
};

#endif