#ifndef MAPMENU_H
#define MAPMENU_H

#include "MenuState.h"
#include "MainMenu.h"
#include "MapBuilder.h"

class MainMenu;
class MapBuilder;
class MapMenu: public MenuState {
private:
	Button* backButton, *createMapButton, *loadMapButton, *editMapButton;
	MainMenu* mm;
	MapBuilder* mb;

public:
	MapMenu( MainMenu *upMenu );
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

	//void getTileClicked( int mx, int my, int &retTileX, int &retTileY );
};

#endif