#include "MapMenu.h"

MapMenu::MapMenu( GLManager* gm ): MenuState(gm) {

}

MapMenu::~MapMenu() {

}

void MapMenu::render() {
	GLManager::clear();
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

	glPopMatrix();
}

void MapMenu::update( float dt ) {
	th += dt*45;
}


void MapMenu::keyPressed( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MapMenu::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MapMenu::mousePressed( int x, int y ) {
	mouseDown = true;
}

void MapMenu::mouseReleased( int x, int y ) {
	mouseDown = false;
}

void MapMenu::mouseMoved( int dx, int dy ) {
	if( mouseDown ) setView(dx, dy);
}
