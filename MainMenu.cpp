#include "MainMenu.h"

MainMenu::MainMenu(/* GLManager* gm ): MenuState(gm*/) {

}

MainMenu::~MainMenu() {

}

void MainMenu::render() {
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

void MainMenu::update( float dt ) {
	th += dt*45;
}


void MainMenu::keyPressed( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MainMenu::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MainMenu::mousePressed( int x, int y ) {
	mouseDown = true;
}

void MainMenu::mouseReleased( int x, int y ) {
	mouseDown = false;
}

void MainMenu::mouseMoved( int dx, int dy ) {
	if( mouseDown ) setView(dx, dy);
}
