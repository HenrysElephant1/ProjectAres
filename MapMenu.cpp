#include "MapMenu.h"

MapMenu::MapMenu( MainMenu* upMenu ) {
	std::string filename = "textures/MapMenuButtons.png";
	GLuint buttonsTex = GLManager::loadTexture(filename);
	filename = "textures/OtherMenuItems.png";
	GLuint labelsTex = GLManager::loadTexture(filename);

		// Project Ares top label
	Button* mainLabel = new Button(0,.7,2,.5);
	mainLabel->setTexture(labelsTex,0,1,.75,1);
	labels.push_back(mainLabel);

	backButton = new Button(0,.3,1,.25);
	backButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(backButton);

	createMapButton = new Button(0,0,1,.25);
	createMapButton->setTexture(buttonsTex,0,1,.75,1);
	buttons.push_back(createMapButton);

	loadMapButton = new Button(0,-.3,1,.25);
	loadMapButton->setTexture(buttonsTex,0,1,.5,.75);
	buttons.push_back(loadMapButton);

	editMapButton = new Button(0,-.6,1,.25);
	editMapButton->setTexture(buttonsTex,0,1,.25,.5);
	buttons.push_back(editMapButton);

	mm = upMenu;
}

MapMenu::~MapMenu() {

}

void MapMenu::render() {
	GLManager::beginRender();
	// glDisable(GL_TEXTURE_2D);
	// glUseProgram(0);

	glPushMatrix();

	double Ex = -10*Sin(th)*Cos(ph);
	double Ey = +10*Sin(ph);
	double Ez = +10*Cos(th)*Cos(ph);
	gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(ph),0);

	glPopMatrix();

	displayOverlay();

	GLManager::endRender();
}

void MapMenu::update( float dt ) {
	// th += dt*45;
}


void MapMenu::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: setNextState(mm, false); break;
	}
}

void MapMenu::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MapMenu::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void MapMenu::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( backButton->isActive() && backButton->testClick(mc.x, mc.y) ) {
		setNextState(mm, false);
	}
	else if( createMapButton->isActive() && createMapButton->testClick(mc.x, mc.y) ) {
		
	}	
	else if( loadMapButton->isActive() && loadMapButton->testClick(mc.x, mc.y) ) {
		
	}	
	else if( editMapButton->isActive() && editMapButton->testClick(mc.x, mc.y) ) {
		
	}	
}

void MapMenu::mouseMoved( int dx, int dy ) {
	// if( mouseDown ) setView(dx, dy);
}
