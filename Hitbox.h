#ifndef HITBOX_H
#define HITBOX_H

#include "GLManager.h"

class Hitbox {
private:
	float locx, locz; // Center location of hitbox
	float width, length, height; // Length is along dir, width is orthogonal to dir
	float dir; // Direction in degrees (0deg is i or {1,0})

	bool colliding;

	// Change of Basis Matrix
	glm::mat3 cbMat; 

	// Vectors for hitbox collision testing (loc = mt+ b)
	glm::vec3 bVecs[12];
	glm::vec3 mVecs[12];

	glm::vec3 bbl;
	glm::vec3 bbr;
	glm::vec3 tbr;
	glm::vec3 tbl;
	glm::vec3 bfl;
	glm::vec3 bfr;
	glm::vec3 tfr;
	glm::vec3 tfl;

	void calcCBMat();
	void calcVecs();

public:
	Hitbox( float w, float l, float x = 0, float z = 0, float d = 0 );
	~Hitbox();

	void update( float x, float z, float d ); // Update the hitbox with new coords and dir
	bool testPointHit( float x, float y, float z ); // Test if point is in the hitbox
	bool testVolumeHit( float x, float y, float z, float radius ); // Test collision with a spherical volume
	bool testVectorHit( glm::vec3 pos, glm::vec3 vec ); // Test collision with a vector vec originating from point pos
	void display();

	friend bool testHitboxCollision( Hitbox *h1, Hitbox *h2 ); // Test collision with another hitbox
};

#endif