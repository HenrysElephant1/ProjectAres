#ifndef HITBOX_H
#define HITBOX_H

class Hitbox {
private:
	float locx, locy; // Center location of hitbox
	float width, length; // Length is along dir, width is orthogonal to dir
	float dir; // Direction in degrees (0deg is i or {1,0})

public:
	Hitbox( float w, float l );
	~Hitbox();

	void update( float x, float y, float d );
	bool testPointHit( float x, float y );
	bool testAreaHit( float x, float y, float radius );
};

#endif