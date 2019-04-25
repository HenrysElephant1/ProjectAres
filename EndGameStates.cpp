#include "EndGameStates.h"

EndGameState::EndGameState( ActiveGame* g ) {
	std::string newTexName = "textures/WinScreenItems.png";
	GLuint newTex = GLManager::loadTexture(newTexName);
	std::string exitTexName = "textures/OtherMenuItems.png";
	GLuint exitTex = GLManager::loadTexture(exitTexName);

	// Game to display in background
	game = g;

	// New Game button
	newGameButton = new Button(0,.0,1,.25);
	newGameButton->setTexture(newTex,0,1,0,.25);
	buttons.push_back(newGameButton);

	// Exit button
	exitButton = new Button(0,-.3,1,.25);
	exitButton->setTexture(exitTex,0,1,0,.25);
	buttons.push_back(exitButton);
}

EndGameState::~EndGameState() {}

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
		game->reset();
		setNextState( game, true );
	}
	else if( exitButton->isActive() && exitButton->testClick(mc.x, mc.y) ) {
		State* nextState = new MainMenu();
		setNextState( nextState, true );
	}
}

void EndGameState::mouseMoved( int dx, int dy ) {

}

P1WinState::P1WinState( ActiveGame* g ): EndGameState(g) {
	std::string endTex = "textures/WinScreenItems.png";
	GLuint useTex = GLManager::loadTexture(endTex);

	Button* winLabel = new Button(0,.4,2,.5);
	winLabel->setTexture(useTex,0,1,.5,.75);
	labels.push_back(winLabel);
}
void P1WinState::update( float dt ) {}

P2WinState::P2WinState( ActiveGame* g ): EndGameState(g) {
	std::string endTex = "textures/WinScreenItems.png";
	GLuint useTex = GLManager::loadTexture(endTex);

	Button* winLabel = new Button(0,.4,2,.5);
	winLabel->setTexture(useTex,0,1,.25,.5);
	labels.push_back(winLabel);
}
void P2WinState::update( float dt ) {}

TieState::TieState( ActiveGame* g ): EndGameState(g) {
	std::string endTex = "textures/WinScreenItems.png";
	GLuint useTex = GLManager::loadTexture(endTex);

	Button* winLabel = new Button(0,.4,2,.5);
	winLabel->setTexture(useTex,0,1,.75,1);
	labels.push_back(winLabel);
}
void TieState::update( float dt ) {}
