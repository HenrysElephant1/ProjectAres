#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>
#include "State.h"
#include "Button.h"

class MenuState: public State {
protected:
	std::vector<Button*> buttons;
	std::vector<Button*> labels; // "Buttons" that will be displayed only

public:
	MenuState(/* GLManager* gm */);
	~MenuState();

	// Display all buttons (and labels)
	void displayOverlay();

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