#include "MainMenu.h"

MainMenu::MainMenu() {
	GLuint buttonsTex = GLManager::loadTexture("textures/MainMenuButtons.png");
	GLuint labelsTex = GLManager::loadTexture("textures/OtherMenuItems.png");

	// Project Ares top label
	Button* mainLabel = new Button(0,.7,2,.5);
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

	p1 = new Player();
	p1->reset(glm::vec3(-5,0,0),25);
	p1->setRGB(0,1,0);
	p2 = new Player();
	p2->reset(glm::vec3(5,0,0),-25);
	p2->setRGB(1,0,1);
	map = new Map();

	// Create other menus with a reference back to self
	pm = new PlayerMenu(this, p1, p2);
	mm = new MapMenu(this);
}

MainMenu::~MainMenu() {
	delete pm;
	delete mm;
}

void MainMenu::render() {
	GLManager::beginRender();

	glPushMatrix();
	double Ex = -10*Sin(th)*Cos(ph);
	double Ey = +10*Sin(ph);
	double Ez = +10*Cos(th)*Cos(ph);
	gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(ph),0);

	glColor3d(0,0,1);
	glBegin(GL_QUADS);
	glVertex3d(1,0,1);
	glVertex3d(1,0,-1);
	glVertex3d(-1,0,-1);
	glVertex3d(-1,0,1);
	glEnd();

	p1->display();
	p2->display();

	glPopMatrix();

	displayOverlay();

	GLManager::endRender();
}

void MainMenu::update( float dt ) {
	// th += dt*45;
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
	State* nextState = new ActiveGame( p1, p2, map );
	setNextState( nextState, true );
}
