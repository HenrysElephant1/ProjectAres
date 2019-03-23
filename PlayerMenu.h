#ifndef PLAYERMENU_H
#define PLAYERMENU_H

#include "MenuState.h"
#include "MainMenu.h"

class MainMenu;
class PlayerMenu: public MenuState {
private:
	Button* backButton;
	MainMenu* mm;

public:
	PlayerMenu( MainMenu* upMenu );
	~PlayerMenu();

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