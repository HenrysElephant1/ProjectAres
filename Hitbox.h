#ifndef HITBOX_H
#define HITBOX_H

#include "GLManager.h"

class Hitbox {
private:
	glm::vec3 loc; // Center location of hitbox
	float width, length, height; // Length is along dir, width is orthogonal to dir
	float dir; // Direction in degrees (0deg is i or {1,0})

	bool colliding;

	// Change of Basis Matrix and its invers
	glm::mat3 cbMat; 
	glm::mat3 invCBMat;

	// Vectors for hitbox collision testing (loc = mt+ b)
	glm::vec3 bVecs[12];
	glm::vec3 mVecs[12];

	// Point vectors for each corner of the hitbox
	// Naming - t/b: Top/Bottom, b/f: Back/Front: l/r: Left/Right
	// bbl serves as the origin point for the hitbox's coordinate system
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
	Hitbox( float w, float l, glm::vec3 initLoc = glm::vec3(0,0,0), float d = 0 );
	~Hitbox();

	void update( glm::vec3 newLoc, float d ); // Update the hitbox with new coords and dir
	bool testPointHit( glm::vec3 pos ); // Test if point is in the hitbox
	bool testVectorHit( glm::vec3 pos, glm::vec3 vec, glm::vec3 *contactPos = NULL, glm::vec3 *contactVec = NULL ); // Test collision with a vector vec originating from point pos
	void display();

	friend bool testHitboxCollision( Hitbox *h1, Hitbox *h2 ); // Test collision with another hitbox
};

#endif