#ifndef MAINMENU_H
#define MAINMENU_H

#include "MenuState.h"

class MainMenu: public MenuState {
private:

public:
	MainMenu(/* GLManager* gm */);
	~MainMenu();

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