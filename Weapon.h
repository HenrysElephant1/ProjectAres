#ifndef WEAPON_H
#define WEAPON_H

#include "Projectile.h"
#include "Model.h"
#include "GLManager.h"

class Weapon {
private:
	Model* model;
	float timer; // Timer for weapon cooldown

	float offx, offy, offz; // Display offsets 
	float firex, firey, firez; // Position to initialize projectile at

public:
	Weapon();
	~Weapon();

	void display();
	void update( float dt );
	Projectile* fire();
};

#endif