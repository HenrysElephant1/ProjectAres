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

	float dir; // Player direction
	glm::vec3 loc; // Player location
	glm::vec3 baseOffset; // Offset for weapon base
	glm::vec3 fireOffset; // Offset from weapon base for projectile initial position

	std::vector<Projectile*> justFired; // Projectiles fired since last frame

	// Get initialization position for projectile - x,y,z,dir are player coords and dir
	glm::vec3 getFireCoords();

public:
	Weapon( glm::vec3 base, glm::vec3 fire );
	virtual ~Weapon();

	void update( glm::vec3 newLoc, float newDir, float dt );
	std::vector<Projectile*> getProjectiles(); // Get projectiles that have been fired since last cycle

	virtual void display() = 0;
	virtual void trigger() = 0; // Handle behavior when fire key is pressed
	virtual void release() = 0; // Handle behavior when fire key is released
};

// Basic that bounces off of walls
class BasicWeapon: public Weapon {
private:

public:
	BasicWeapon( glm::vec3 base );
	~BasicWeapon();

	void display(); // Temporary - will just display model from superclass in future
	void trigger();
	void release();
};

// Weapon that bounces off of walls
class ReboundWeapon: public Weapon {
private:

public:
	ReboundWeapon( glm::vec3 base );
	~ReboundWeapon();

	void display(); // Temporary - will just display model from superclass in future
	void trigger();
	void release();
};

#endif