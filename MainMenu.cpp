#include "MainMenu.h"

MainMenu::MainMenu() {
	std::string filename = "textures/MainMenuButtons.png";
	GLuint buttonsTex = GLManager::loadTexture(filename);
	filename = "textures/OtherMenuItems.png";
	GLuint labelsTex = GLManager::loadTexture(filename);

	// Project Ares top label
	Button* mainLabel = new Button(0,.7,3,.75);
	mainLabel->setTexture(labelsTex,0,1,.75,1);
	labels.push_back(mainLabel);

	// Play button
	playButton = new Button(0,.3,1,.25);
	playButton->setTexture(buttonsTex,0,1,.75,1);
	buttons.push_back(playButton);

	// Map Menu button
	mapMenuButton = new Button(0,0,1,.25);
	mapMenuButton->setTexture(buttonsTex,0,1,.5,.75);
	buttons.push_back(mapMenuButton);

	// Player Menu button
	playerMenuButton = new Button(0,-.3,1,.25);
	playerMenuButton->setTexture(buttonsTex,0,1,.25,.5);
	buttons.push_back(playerMenuButton);

	// Quit button
	quitButton = new Button(0,-.6,1,.25);
	quitButton->setTexture(buttonsTex,0,1,0,.25);
	buttons.push_back(quitButton);

	// Initialize players and map
	p1 = new Player();
	p1->reset(glm::vec3(-5,0,0),45);
	p1->setRGB(COLOR_OPTIONS[P1_DEFAULT_COLOR][0],COLOR_OPTIONS[P1_DEFAULT_COLOR][1],COLOR_OPTIONS[P1_DEFAULT_COLOR][2]);

	p2 = new Player();
	p2->reset(glm::vec3(5,0,0),-45);
	p2->setRGB(COLOR_OPTIONS[P2_DEFAULT_COLOR][0],COLOR_OPTIONS[P2_DEFAULT_COLOR][1],COLOR_OPTIONS[P2_DEFAULT_COLOR][2]);

	//map = new Map();
	map = Map::loadMap(0);

	// Create other menus with a reference back to self
	pm = new PlayerMenu(this, p1, p2);
	mm = new MapMenu(this, map);
}

MainMenu::~MainMenu() {
	delete pm;
	delete mm;
}

void MainMenu::render() {
	GLManager::beginRender();

	glPushMatrix();
	gluLookAt(0,10,.01, 0,1,0, 0,Cos(ph),0);

	p1->display();
	p2->display();

	glPopMatrix();

	displayOverlay();

	GLManager::endRender();
}

void MainMenu::update( float dt ) {

}


void MainMenu::keyPressed( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_ESCAPE: GLManager::QUIT = true; break;
	// }
}

void MainMenu::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MainMenu::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void MainMenu::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( playButton->isActive() && playButton->testClick(mc.x, mc.y) ) {
		createGame();
	}
	else if( mapMenuButton->isActive() && mapMenuButton->testClick(mc.x, mc.y) ) {
		setNextState(mm, false);
	}
	else if( playerMenuButton->isActive() && playerMenuButton->testClick(mc.x, mc.y) ) {
		setNextState(pm, false);
	}
	else if( quitButton->isActive() && quitButton->testClick(mc.x, mc.y) ) {
		GLManager::QUIT = true;
	}
}

void MainMenu::mouseMoved( int dx, int dy ) {
	// if( mouseDown ) setView(dx, dy);
}

void MainMenu::createGame() {
	p1->reset(map->getP1StartPos(),0);
	p2->reset(map->getP2StartPos(),180);
	State* nextState = new ActiveGame( p1, p2, map );
	setNextState( nextState, true );
}