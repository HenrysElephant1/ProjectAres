#ifndef ACTIVEGAME_H
#define ACTIVEGAME_H

#include <vector>

#include "State.h"
#include "MenuState.h"
#include "PauseMenu.h"

#include "Player.h"
#include "Map.h"
#include "Projectile.h"
#include "Hitbox.h"

class ActiveGame: public State {
private:
	Player *p1, *p2;
	Map *map;
	std::vector<Projectile*> projectiles;

	float camX, camY, camZ; // Camera coordinates - static for now

	void pauseGame();

public:
	ActiveGame( Player *play1, Player *play2, Map *m );
	~ActiveGame();

	// Functions inherited from State
	void render();
	void update( float dt );

	// Handlers inherited from State
	void keyPressed( SDL_Keycode key );
	void keyReleased( SDL_Keycode key );
	void mousePressed( int x, int y );
	void mouseReleased( int x, int y );
	void mouseMoved( int dx, int dy );
};

#endif