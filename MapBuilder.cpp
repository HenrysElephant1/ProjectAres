#include "MapBuilder.h"

MapBuilder::MapBuilder( MapMenu* upMenu ) {
	std::string filename = "textures/OtherMenuItems.png";
	GLuint labelsTex = GLManager::loadTexture(filename);

	// Project Ares top label
	Button* mainLabel = new Button(0,.7,2,.5);
	mainLabel->setTexture(labelsTex,0,1,.75,1);
	labels.push_back(mainLabel);

	backButton = new Button(0,.3,1,.25);
	backButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(backButton);

	mm = upMenu;
}

MapBuilder::~MapBuilder() {

}

void MapBuilder::render() {
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

void MapBuilder::update( float dt ) {
	// th += dt*45;
}


void MapBuilder::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: setNextState(mm, false); break;
	}
}

void MapBuilder::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MapBuilder::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void MapBuilder::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( backButton->isActive() && backButton->testClick(mc.x, mc.y) ) {
		setNextState(mm, false);
	}
}

void MapBuilder::mouseMoved( int dx, int dy ) {
	// if( mouseDown ) setView(dx, dy);
}
