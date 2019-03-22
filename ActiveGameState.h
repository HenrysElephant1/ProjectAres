#ifndef ACTIVEGAMESTATE_H
#define ACTIVEGAMESTATE_H

#include "State.h"

class ActiveGameState: public State {
private:
	bool mouseDown = false;
public:
	ActiveGameState( int width, int height );
	~ActiveGameState();

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