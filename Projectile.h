#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Model.h"
#include "GLManager.h"

#define BASIC_PROJECTILE_SPEED 40;

class Projectile {
protected:
	Model* model;
	float timer;
	float locx, locy, locz;

public:
	Projectile( float x, float y, float z );
	virtual ~Projectile();

	virtual void display() = 0;
	virtual void update( float dt ) = 0;

	bool destroy();
};


class BasicProjectile: public Projectile {
private:
	float velx, velz;

public:
	BasicProjectile( float x, float y, float z, float dir );
	~BasicProjectile();

	void display();
	void update( float dt );
};

#endif