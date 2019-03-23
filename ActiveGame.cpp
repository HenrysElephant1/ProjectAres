#include "ActiveGame.h"

ActiveGame::ActiveGame() {

}

ActiveGame::~ActiveGame() {

}

void ActiveGame::render() {
	GLManager::beginRender();
	
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

	GLManager::endRender();
}

void ActiveGame::update( float dt ) {
	th += dt*45;
}


void ActiveGame::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: State* nextState = new PauseMenu(this); setNextState(nextState); break;
	}
}

void ActiveGame::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void ActiveGame::mousePressed( int x, int y ) {
	mouseDown = true;
}

void ActiveGame::mouseReleased( int x, int y ) {
	mouseDown = false;
}

void ActiveGame::mouseMoved( int dx, int dy ) {
	if( mouseDown ) setView(dx, dy);
}
