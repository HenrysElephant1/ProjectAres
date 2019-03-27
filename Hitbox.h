#ifndef HITBOX_H
#define HITBOX_H

class Hitbox {
private:
	float locx, locz; // Center location of hitbox
	float width, length; // Length is along dir, width is orthogonal to dir
	float dir; // Direction in degrees (0deg is i or {1,0})

public:
	Hitbox( float w, float l );
	~Hitbox();

	void update( float x, float z, float d );
	bool testPointHit( float x, float z );
	bool testAreaHit( float x, float z, float radius );
};

#endif