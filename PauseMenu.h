#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "MenuState.h"
#include "ActiveGame.h"
#include "MainMenu.h"

class ActiveGame;
class PauseMenu: public MenuState {
private:
	ActiveGame* game;
	Button *resumeButton, *exitButton;

public:
	PauseMenu( ActiveGame* g );
	~PauseMenu();

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