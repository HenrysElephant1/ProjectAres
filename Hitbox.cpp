#include "Hitbox.h"

Hitbox::Hitbox( float w, float l ) {
	width = w;
	length = l;
}

Hitbox::~Hitbox() {

}

void Hitbox::update( float x, float z, float d ) {
	locx = x;
	locz = z;
	dir = d;
}

bool Hitbox::testPointHit( float x, float z ) {
	return true;
}

bool Hitbox::testAreaHit( float x, float z, float radius ) {
	return true;
}