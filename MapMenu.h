#ifndef MAPMENU_H
#define MAPMENU_H

#include "MenuState.h"

class MapMenu: public MenuState {
private:

public:
	MapMenu( GLManager* gm );
	~MapMenu();

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