#include "PausedGameState.h"

PausedGameState::PausedGameState( GLManager* gm ): State(gm) {

}

PausedGameState::~PausedGameState() {

}

void PausedGameState::render() {
	GLManager::clear();
	glPushMatrix();

	double Ex = -10*Sin(th)*Cos(ph);
	double Ey = +10*Sin(ph);
	double Ez = +10*Cos(th)*Cos(ph);
	gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(ph),0);

	glColor3d(0,1,0);
	glBegin(GL_QUADS);
	glVertex3d(1,0,1);
	glVertex3d(1,0,-1);
	glVertex3d(-1,0,-1);
	glVertex3d(-1,0,1);
	glEnd();

	glPopMatrix();
}

void PausedGameState::update( float dt ) {
	th += dt*45;
}


void PausedGameState::keyPressed( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void PausedGameState::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void PausedGameState::mousePressed( int x, int y ) {
	mouseDown = true;
}

void PausedGameState::mouseReleased( int x, int y ) {
	mouseDown = false;
}

void PausedGameState::mouseMoved( int dx, int dy ) {
	if( mouseDown ) setView(dx, dy);
}
