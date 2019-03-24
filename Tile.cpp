#include "Tile.h"

Tile::Tile() {
	hitboxes = new Hitbox*[1];
}

Tile::~Tile() {
	delete[] hitboxes;
}

void Tile::display() {

}