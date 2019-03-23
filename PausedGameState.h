#ifndef PAUSEDGAMESTATE_H
#define PAUSEDGAMESTATE_H

#include "State.h"
#include "ActiveGameState.h"
#include "MenuState.h"

class PausedGameState: public State {
private:

public:
	PausedGameState( GLManager* gm );
	~PausedGameState();

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