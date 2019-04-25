#ifndef ENDGAMESTATES_H
#define ENDGAMESTATES_H

#include "MenuState.h"
#include "ActiveGame.h"
#include "MainMenu.h"

class ActiveGame;
class EndGameState: public MenuState {
private:
	ActiveGame* game;
	Button *newGameButton, *exitButton;

public:
	EndGameState( ActiveGame* g );
	~EndGameState();

	// Functions inherited from State
	void render();
	virtual void update( float dt ) = 0; // Only virtual to force abstract class

	// Handlers inherited from State
	void keyPressed( SDL_Keycode key );
	void keyReleased( SDL_Keycode key );
	void mousePressed( int x, int y );
	void mouseReleased( int x, int y );
	void mouseMoved( int dx, int dy );
};

class P1WinState: public EndGameState {
public:
	P1WinState( ActiveGame* g );
	void update( float dt );
};

class P2WinState: public EndGameState {
public:
	P2WinState( ActiveGame* g );
	void update( float dt );	
};

class TieState: public EndGameState {
public:
	TieState( ActiveGame* g );
	void update( float dt );
};

#endif