#include "GameState.h"

GameState::GameState( int width, int height ): State(width, height) {

}

GameState::~GameState() {

}

void GameState::render() {
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

void GameState::update( float dt ) {

}
