#include "PauseMenu.h"

PauseMenu::PauseMenu( ActiveGame* g ) {
	GLuint labelsTex = GLManager::loadTexture("textures/OtherMenuItems.png");

	// Game to return to
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

PauseMenu::~PauseMenu() {

}

void PauseMenu::render() {
	GLManager::beginRender();

	game->render();

	displayOverlay();

	GLManager::endRender();
}

void PauseMenu::update( float dt ) {

}


void PauseMenu::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: setNextState(game, false); break;
	}
}

void PauseMenu::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void PauseMenu::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void PauseMenu::mouseReleased( int x, int y ) {
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

void PauseMenu::mouseMoved( int dx, int dy ) {

}
