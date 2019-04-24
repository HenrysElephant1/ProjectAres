#ifndef TILE_H
#define TILE_H

#include "Hitbox.h"
#include "GLManager.h"
#include "Player.h"
#include "Projectile.h"

#define TILE_SIZE 6

class Tile {
protected:
	enum Type {
		FLOOR,
		WALL
	};

	int x, y;
	int hitbox_count;
	Hitbox** hitboxes; // Tile may have multiple hitboxes
	int texture;
	
	static std::string floorTex;

public:
	Tile( int x, int y );
	virtual ~Tile();
	
	virtual void display() = 0;
	static Tile* createTile(int x, int y, int tileType);
	void testPlayerCollision( Player *p );
	void testProjectileCollision( Projectile *p );
};

class FloorTile : public Tile {
public:
	FloorTile( int x, int y );
	void display();
};

class WallTile : public Tile {
public:
	WallTile( int x, int y );
	void display();
};

#endif