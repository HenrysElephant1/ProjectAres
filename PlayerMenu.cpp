#include "PlayerMenu.h"

PlayerMenu::PlayerMenu( GLManager* gm ): MenuState(gm) {

}

PlayerMenu::~PlayerMenu() {

}

void PlayerMenu::render() {
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

void PlayerMenu::update( float dt ) {
	th += dt*45;
}


void PlayerMenu::keyPressed( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void PlayerMenu::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void PlayerMenu::mousePressed( int x, int y ) {
	mouseDown = true;
}

void PlayerMenu::mouseReleased( int x, int y ) {
	mouseDown = false;
}

void PlayerMenu::mouseMoved( int dx, int dy ) {
	if( mouseDown ) setView(dx, dy);
}
