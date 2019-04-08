#ifndef WEAPON_H
#define WEAPON_H

#include <vector>

#include "Projectile.h"
#include "Model.h"
#include "GLManager.h"

class Weapon {
protected:
	Model* model;
	float timer; // Timer for weapon cooldown
	bool triggered;

	float offx, offy, offz; // Offset for weapon base
	float firex, firey, firez; // Offset from weapon base for projectile initial position

	std::vector<Projectile*> justFired;

	// Get initialization position for projectile - x,y,z,dir are player coords and dir
	void getFireCoords( float x, float y, float z, float dir, float &retx, float &rety, float &retz );
	virtual void fire( float x, float y, float z, float dir ) = 0;

public:
	Weapon( float ox, float oy, float oz, float fx, float fy, float fz );
	virtual ~Weapon();

	void update( float dt );
	std::vector<Projectile*> getProjectiles(); // Get projectiles that have been fired since last cycle

	virtual void display() = 0;
	virtual void trigger( float x, float y, float z, float dir ) = 0; // Handle behavior when fire key is pressed
	virtual void release() = 0; // Handle behavior when fire key is released
};

// Basic that bounces off of walls
class BasicWeapon: public Weapon {
private:
	void fire( float x, float y, float z, float dir );

public:
	BasicWeapon( float ox, float oy, float oz );
	~BasicWeapon();

	void display(); // Temporary - will just display model from superclass in future
	void trigger( float x, float y, float z, float dir );
	void release();
};

#endif