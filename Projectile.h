#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Model.h"
#include "GLManager.h"

class Projectile {
private:
	Model* model;
	float timer;
	float locx, locy, locz;

public:
	Projectile( float x, float y, float z );
	~Projectile();

	void display();
	void update( float dt );
};

#endif