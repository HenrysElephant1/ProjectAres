#include "WinStates.h"

WinState::WinState( ActiveGame* g ) {
	GLuint labelsTex = GLManager::loadTexture("textures/OtherMenuItems.png");

	// Game to display in background
	game = g;

	// Resume button
	resumeButton = new Button(0,.15,1,.25);
	resumeButton->setTexture(labelsTex,0,1,.25,.5);
	buttons.push_back(resumeButton);

	// Exit button
	exitButton = new Button(0,-.15,1,.25);
	exitButton->setTexture(labelsTex,0,1,0,.25);
	buttons.push_back(exitButton);
}

WinState::~WinState() {

}

void WinState::render() {
	GLManager::beginRender();

	game->render();

	displayOverlay();

	GLManager::endRender();
}

void WinState::update( float dt ) {

}


void WinState::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		// case SDLK_ESCAPE: setNextState(game, false); break;
	}
}

void WinState::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void WinState::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void WinState::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( resumeButton->isActive() && resumeButton->testClick(mc.x, mc.y) ) {
		setNextState(game, false);
	}
	else if( exitButton->isActive() && exitButton->testClick(mc.x, mc.y) ) {
		State* nextState = new MainMenu();
		setNextState( nextState, true );
	}
}

void WinState::mouseMoved( int dx, int dy ) {

}
