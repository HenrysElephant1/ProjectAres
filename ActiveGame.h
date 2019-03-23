#ifndef ACTIVEGAME_H
#define ACTIVEGAME_H

#include "State.h"
#include "MenuState.h"
#include "PauseMenu.h"

class ActiveGame: public State {
private:

public:
	ActiveGame();
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