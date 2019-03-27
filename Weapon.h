#ifndef WEAPON_H
#define WEAPON_H

#include "Projectile.h"
#include "Model.h"
#include "GLManager.h"

class Weapon {
protected:
	Model* model;
	float timer; // Timer for weapon cooldown

	float offx, offy, offz; // Offset for weapon base
	float firex, firey, firez; // Offset from weapon base for projectile initial position

	// Get initialization position for projectile - x,y,z,dir are player coords and dir
	void getFireCoords( float x, float y, float z, float dir, float &retx, float &rety, float &retz );

public:
	Weapon( float ox, float oy, float oz, float fx, float fy, float fz );
	virtual ~Weapon();

	virtual void display() = 0;
	void update( float dt );
	virtual Projectile* fire( float x, float y, float z, float dir ) = 0;
};

// Basic that bounces off of walls
class BasicWeapon: public Weapon {
private:

public:
	BasicWeapon( float ox, float oy, float oz );
	~BasicWeapon();

	Projectile* fire( float x, float y, float z, float dir );
	void display(); // Temporary - will just display model from superclass in future
};

#endif