#include "ActiveGame.h"

ActiveGame::ActiveGame( Player *play1, Player *play2, Map *m ) {
	p1 = play1;
	p2 = play2;
	map = m;
	viewHeight = GLManager::getMapViewHeight( map->getUnitWidth(), map->getUnitHeight() );
	// std::cout << "Got Height " << viewHeight << std::endl;
	ph = 90;
	endGameTimer = 3;
}

ActiveGame::~ActiveGame() {

}

void ActiveGame::render() {
	GLManager::beginRender();
	
	glm::vec3 mapLoc = map->getCenter();
	glm::vec3 eyeLoc = mapLoc + glm::vec3(0,viewHeight,0);

	glPushMatrix();
	double Mx = mapLoc.x;
	double My = mapLoc.y;
	double Mz = mapLoc.z;
	double Ex = Mx + eyeLoc.y*Sin(th)*Cos(ph);
	double Ey = My + eyeLoc.y*Sin(ph);
	double Ez = Mz + eyeLoc.y*Cos(th)*Cos(ph);
	gluLookAt(Ex,Ey,Ez, Mx,My,Mz, 0,Cos(ph),0);

	GLManager::doLighting();

	map->display();
	p1->display();
	p2->display();
	for( int i=0; i<projectiles.size(); i++ ) {
		projectiles[i]->display();
	}

	glPopMatrix();

	p1->displayHealthBar(true);
	p2->displayHealthBar(false);

	GLManager::endRender();
	GLManager::debug("Game Render");
}

void ActiveGame::update( float dt ) {
	p1->update(dt);
	p2->update(dt);

	// Test player hitbox collision
	// Must test both to prevent both from moving
	if( p1->getHealth() > 0 && p2->getHealth() > 0 ) {
		p1->testWorldCollision( p2->getHitbox() );
		p2->testWorldCollision( p1->getHitbox() );
	}
	map->testPlayerCollision( p1 );
	map->testPlayerCollision( p2 );

	// Get projectiles fired and add them to vector
	std::vector<Projectile*> p1Proj = p1->getProjectiles();
	std::vector<Projectile*> p2Proj = p2->getProjectiles();
	projectiles.insert( projectiles.end(), p1Proj.begin(), p1Proj.end() );
	projectiles.insert( projectiles.end(), p2Proj.begin(), p2Proj.end() );

	for( int i=0; i<projectiles.size(); i++ ) {
		projectiles[i]->update(dt);
		map->testProjectileCollision( projectiles[i] );

		// Only test a player hit if appropriate
		if( projectiles[i]->shouldTestPlayerHit() ) {
			p1->testHit( projectiles[i] );
			p2->testHit( projectiles[i] );
		}

		// Delete projectile if necessary
		if( projectiles[i]->shouldDestroy() ) {
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i--);
		}
	}

	if( p1->getHealth() <= 0 || p2->getHealth() <= 0 )
		endGameTimer -= dt;

	if( endGameTimer <= 0 ) {
		if( p1->getHealth() <= 0 && p2->getHealth() <= 0 )
			setNextState( new TieState(this), false );
		else if( p1->getHealth() <= 0 )
			setNextState( new P2WinState(this), false );
		else
			setNextState( new P1WinState(this), false );
	}
}


void ActiveGame::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: pauseGame(); break;

		// P1 controls
		case SDLK_r: p1->setForward(true); break;
		case SDLK_f: p1->setBackward(true); break;
		case SDLK_d: p1->setLeft(true); break;
		case SDLK_g: p1->setRight(true); break;
		case SDLK_q: p1->triggerWeapon1(); break;
		case SDLK_w: p1->triggerWeapon2(); break;

		// P2 controls
		case SDLK_o: p2->setForward(true); break;
		case SDLK_l: p2->setBackward(true); break;
		case SDLK_k: p2->setLeft(true); break;
		case SDLK_SEMICOLON: p2->setRight(true); break;
		case SDLK_RIGHTBRACKET: p2->triggerWeapon1(); break;
		case SDLK_BACKSLASH: p2->triggerWeapon2(); break;
	}
}

void ActiveGame::keyReleased( SDL_Keycode key ) {
	switch( key ) {
		// P1 controls
		case SDLK_r: p1->setForward(false); break;
		case SDLK_f: p1->setBackward(false); break;
		case SDLK_d: p1->setLeft(false); break;
		case SDLK_g: p1->setRight(false); break;
		case SDLK_q: p1->releaseWeapon1(); break;
		case SDLK_w: p1->releaseWeapon2(); break;

		// P2 controls
		case SDLK_o: p2->setForward(false); break;
		case SDLK_l: p2->setBackward(false); break;
		case SDLK_k: p2->setLeft(false); break;
		case SDLK_SEMICOLON: p2->setRight(false); break;
		case SDLK_RIGHTBRACKET: p2->releaseWeapon1(); break;
		case SDLK_BACKSLASH: p2->releaseWeapon2(); break;
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

void ActiveGame::reset() {
	p1->reset(map->getP1StartPos(),0);
	p2->reset(map->getP2StartPos(),180);
	projectiles.clear();
	endGameTimer = 3;
}
