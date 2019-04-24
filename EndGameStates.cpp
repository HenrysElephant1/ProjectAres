#include "EndGameStates.h"

EndGameState::EndGameState( ActiveGame* g ) {
	std::string menuTex = "textures/OtherMenuItems.png";
	GLuint labelsTex = GLManager::loadTexture(menuTex);

	// Game to display in background
	game = g;

	// New Game button
	newGameButton = new Button(0,.15,1,.25);
	newGameButton->setTexture(labelsTex,0,1,.25,.5);
	buttons.push_back(newGameButton);

	// Exit button
	exitButton = new Button(0,-.15,1,.25);
	exitButton->setTexture(labelsTex,0,1,0,.25);
	buttons.push_back(exitButton);
}

EndGameState::~EndGameState() {

}

void EndGameState::render() {
	GLManager::beginRender();

	game->render();

	displayOverlay();

	GLManager::endRender();
}


void EndGameState::keyPressed( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_ESCAPE: setNextState(game, false); break;
	// }
}

void EndGameState::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void EndGameState::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void EndGameState::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( newGameButton->isActive() && newGameButton->testClick(mc.x, mc.y) ) {
		setNextState(game, true);
	}
	else if( exitButton->isActive() && exitButton->testClick(mc.x, mc.y) ) {
		State* nextState = new MainMenu();
		setNextState( nextState, true );
	}
}

void EndGameState::mouseMoved( int dx, int dy ) {

}

P1WinState::P1WinState( ActiveGame* g ): EndGameState(g) {}
void P1WinState::update( float dt ) {}

P2WinState::P2WinState( ActiveGame* g ): EndGameState(g) {}
void P2WinState::update( float dt ) {}

TieState::TieState( ActiveGame* g ): EndGameState(g) {}
void TieState::update( float dt ) {}
