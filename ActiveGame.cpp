#include "ActiveGame.h"

ActiveGame::ActiveGame( Player *play1, Player *play2, Map *m ) {
	p1 = play1;
	p2 = play2;
	map = m;
	camX = 0;
	camY = 100;
	camZ = 0;
}

ActiveGame::~ActiveGame() {

}

void ActiveGame::render() {
	GLManager::beginRender();
	
	glPushMatrix();
	// double Ex = -10*Sin(th)*Cos(ph);
	// double Ey = +10*Sin(ph);
	// double Ez = +10*Cos(th)*Cos(ph);
	// gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(ph),0);
	gluLookAt(camX, camY, camZ, 0,0,0, 0,0,-1);

	map->display();
	p1->display();
	p2->display();
	for( int i=0; i<projectiles.size(); i++ ) {
		projectiles[i]->display();
	}

	glPopMatrix();

	GLManager::endRender();
	GLManager::debug("Game Render");
}

void ActiveGame::update( float dt ) {
	p1->update(dt, projectiles);
	p2->update(dt, projectiles);
	for( int i=0; i<projectiles.size(); i++ ) {
		projectiles[i]->update(dt);
		if( projectiles[i]->destroy() ) {
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i--);
		}
	}
	testHitboxCollision( p1->getHitbox(), p2->getHitbox() );
}


void ActiveGame::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: pauseGame(); break;

		// P1 controls
		case SDLK_r: p1->setForward(true); break;
		case SDLK_f: p1->setBackward(true); break;
		case SDLK_d: p1->setLeft(true); break;
		case SDLK_g: p1->setRight(true); break;
		case SDLK_q: projectiles.push_back( p1->fireWeapon1() ); break;
		case SDLK_w: projectiles.push_back( p1->fireWeapon2() ); break;

		// P2 controls
		case SDLK_o: p2->setForward(true); break;
		case SDLK_l: p2->setBackward(true); break;
		case SDLK_k: p2->setLeft(true); break;
		case SDLK_SEMICOLON: p2->setRight(true); break;
		case SDLK_RIGHTBRACKET: projectiles.push_back( p2->fireWeapon1() ); break;
		case SDLK_BACKSLASH: projectiles.push_back( p2->fireWeapon2() ); break;

		case SDLK_UP:    camZ++; break;
		case SDLK_DOWN:  camZ--; break;
		case SDLK_LEFT:  camX--; break;
		case SDLK_RIGHT: camX++; break;
	}
}

void ActiveGame::keyReleased( SDL_Keycode key ) {
	switch( key ) {
		// P1 controls
		case SDLK_r: p1->setForward(false); break;
		case SDLK_f: p1->setBackward(false); break;
		case SDLK_d: p1->setLeft(false); break;
		case SDLK_g: p1->setRight(false); break;

		// P2 controls
		case SDLK_o: p2->setForward(false); break;
		case SDLK_l: p2->setBackward(false); break;
		case SDLK_k: p2->setLeft(false); break;
		case SDLK_SEMICOLON: p2->setRight(false); break;
	}
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

void ActiveGame::pauseGame() {
	State* nextState = new PauseMenu(this);
	setNextState(nextState, false); 
}
