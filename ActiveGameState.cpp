#include "ActiveGameState.h"

ActiveGameState::ActiveGameState( int width, int height ): State(width, height) {

}

ActiveGameState::~ActiveGameState() {

}

void ActiveGameState::render() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glPushMatrix();

	double Ex = -10*Sin(th)*Cos(ph);
	double Ey = +10*Sin(ph);
	double Ez = +10*Cos(th)*Cos(ph);
	gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(ph),0);

	glColor3d(1,0,0);
	glBegin(GL_QUADS);
	glVertex3d(1,0,1);
	glVertex3d(1,0,-1);
	glVertex3d(-1,0,-1);
	glVertex3d(-1,0,1);
	glEnd();

	glPopMatrix();
}

void ActiveGameState::update( float dt ) {
	th += dt*45;
}


void ActiveGameState::keyPressed( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void ActiveGameState::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void ActiveGameState::mousePressed( int x, int y ) {
	mouseDown = true;
}

void ActiveGameState::mouseReleased( int x, int y ) {
	mouseDown = false;
}

void ActiveGameState::mouseMoved( int dx, int dy ) {
	if( mouseDown ) setView(dx, dy);
}
