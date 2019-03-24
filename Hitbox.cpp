#include "Hitbox.h"

Hitbox::Hitbox( float w, float l ) {
	width = w;
	length = l;
}

Hitbox::~Hitbox() {

}

void Hitbox::update( float x, float y, float d ) {
	locx = x;
	locy = y;
	dir = d;
}

bool Hitbox::testPointHit( float x, float y ) {
	return true;
}

bool Hitbox::testAreaHit( float x, float y, float radius ) {
	return true;
}