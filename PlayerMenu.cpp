#include "PlayerMenu.h"

PlayerMenu::PlayerMenu( MainMenu* upMenu, Player* play1, Player* play2 ) {
	GLuint labelsTex = GLManager::loadTexture("textures/OtherMenuItems.png");

	backButton = new Button(0,.7,1,.25);
	backButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(backButton);

	mm = upMenu;
	p1 = play1;
	p2 = play2;
}

PlayerMenu::~PlayerMenu() {

}

void PlayerMenu::render() {
	GLManager::beginRender();

	glPushMatrix();

	double Ex = -10*Sin(th)*Cos(ph);
	double Ey = +10*Sin(ph);
	double Ez = +10*Cos(th)*Cos(ph);
	gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(ph),0);

	glColor3d(1,.5,0);
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

void PlayerMenu::update( float dt ) {
	// th += dt*45;
}


void PlayerMenu::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: setNextState(mm, false); break;
	}
}

void PlayerMenu::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void PlayerMenu::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void PlayerMenu::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( backButton->isActive() && backButton->testClick(mc.x, mc.y) ) {
		setNextState(mm, false);
	}
}

void PlayerMenu::mouseMoved( int dx, int dy ) {
	// if( mouseDown ) setView(dx, dy);
}
