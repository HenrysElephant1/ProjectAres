#ifndef PLAYERMENU_H
#define PLAYERMENU_H

#include "MenuState.h"
#include "MainMenu.h"
#include "Player.h"

const float COLOR_OPTIONS[][3] = {
	{1.0, 0.0, 0.0},
	{1.0, 0.5, 0.0},
	{1.0, 1.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 1.0, 1.0},
	{0.0, 0.0, 1.0},
	{1.0, 0.0, 1.0},
};
const int N_COLORS = sizeof(COLOR_OPTIONS)/sizeof(float)/3;

class MainMenu;
class PlayerMenu: public MenuState {
private:
	Button* backButton;
	Button* p1ColorButtons[N_COLORS];
	Button* p2ColorButtons[N_COLORS];
	Button* p1Weapon1Buttons[3];
	Button* p2Weapon1Buttons[3];
	Button* p1Weapon2Buttons[3];
	Button* p2Weapon2Buttons[3];
	MainMenu* mm;

	GLuint labelsTex, pmItems;

	Player *p1, *p2;

public:
	PlayerMenu( MainMenu* upMenu, Player* play1, Player* play2 );
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