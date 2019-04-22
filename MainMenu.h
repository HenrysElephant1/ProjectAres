#ifndef MAINMENU_H
#define MAINMENU_H

#include "MenuState.h"
#include "MapMenu.h"
#include "PlayerMenu.h"
#include "ActiveGame.h"
#include "Player.h"
#include "Map.h"

#define P1_DEFAULT_COLOR 0
#define P2_DEFAULT_COLOR 1

class MapMenu;
class PlayerMenu;
class MainMenu: public MenuState {
private:
	Button *playButton, *mapMenuButton, *playerMenuButton, *quitButton;
	PlayerMenu *pm;
	MapMenu *mm;

	Map *map;

	Player *p1, *p2;

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

	void setMap(int newMap);
	void createGame();
};

#endif