#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "ActiveGameState.h"
#include "PausedGameState.h"
#include "Button.h"

class MenuState: public State {
private:

public:
	MenuState( GLManager* gm );
	~MenuState();

	// Functions inherited from State
	virtual void render() = 0;
	virtual void update( float dt ) = 0;

	// Handlers inherited from State
	virtual void keyPressed( SDL_Keycode key ) = 0;
	virtual void keyReleased( SDL_Keycode key ) = 0;
	virtual void mousePressed( int x, int y ) = 0;
	virtual void mouseReleased( int x, int y ) = 0;
	virtual void mouseMoved( int dx, int dy ) = 0;
};

#endif