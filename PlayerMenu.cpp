#include "PlayerMenu.h"

PlayerMenu::PlayerMenu( MainMenu* upMenu, Player* play1, Player* play2 ) {
	labelsTex = GLManager::loadTexture("textures/OtherMenuItems.png");
	pmItems = GLManager::loadTexture("textures/PlayerMenuItems.png");

	backButton = new Button(0,.7,1,.25);
	backButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(backButton);

	mm = upMenu;
	p1 = play1;
	p2 = play2;

	for( int i=0; i<N_COLORS; i++ ) {
		float yloc = ((N_COLORS-2)/2-i)*.12;
		p1ColorButtons[i] = new Button(-.15,yloc,.2,.1,COLOR_OPTIONS[i][0],COLOR_OPTIONS[i][1],COLOR_OPTIONS[i][2]);
		p1ColorButtons[i]->setTexture(pmItems,(i==P1_DEFAULT_COLOR?.5:0),(i==P1_DEFAULT_COLOR?1:.5),.75,1);
		buttons.push_back(p1ColorButtons[i]);
		p2ColorButtons[i] = new Button(.15,yloc,.2,.1,COLOR_OPTIONS[i][0],COLOR_OPTIONS[i][1],COLOR_OPTIONS[i][2]);
		p2ColorButtons[i]->setTexture(pmItems,(i==P2_DEFAULT_COLOR?.5:0),(i==P2_DEFAULT_COLOR?1:.5),.75,1);
		buttons.push_back(p2ColorButtons[i]);
	}
}

PlayerMenu::~PlayerMenu() {}

void PlayerMenu::render() {
	GLManager::beginRender();

	glPushMatrix();

	gluLookAt(0,2,10, 0,1,0, 0,Cos(ph),0);

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
	else {
		for( int i=0; i<N_COLORS; i++ ) {
			if( p1ColorButtons[i]->isActive() && p1ColorButtons[i]->testClick(mc.x, mc.y) ) {
				p1->setRGB(COLOR_OPTIONS[i][0], COLOR_OPTIONS[i][1], COLOR_OPTIONS[i][2]);
				for( int j=0; j<N_COLORS; j++ ) {
					if( j == i ) p1ColorButtons[j]->setTexture(pmItems,.5,1,.75,1);
					else p1ColorButtons[j]->setTexture(pmItems,0,.5,.75,1);
				}
				goto done;
			}
		}
		for( int i=0; i<N_COLORS; i++ ) {
			if( p2ColorButtons[i]->isActive() && p2ColorButtons[i]->testClick(mc.x, mc.y) ) {
				p2->setRGB(COLOR_OPTIONS[i][0], COLOR_OPTIONS[i][1], COLOR_OPTIONS[i][2]);
				for( int j=0; j<N_COLORS; j++ ) {
					if( j == i ) p2ColorButtons[j]->setTexture(pmItems,.5,1,.75,1);
					else p2ColorButtons[j]->setTexture(pmItems,0,.5,.75,1);
				}
				goto done;
			}
		}
	}

	done:
	return;
}

void PlayerMenu::mouseMoved( int dx, int dy ) {
	// if( mouseDown ) setView(dx, dy);
}
