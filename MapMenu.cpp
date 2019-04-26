#include "MapMenu.h"

MapMenu::MapMenu( MainMenu* upMenu ) {
	std::string filename = "textures/OtherMenuItems.png";
	labelsTex = GLManager::loadTexture(filename);

	filename = "textures/PlayerMenuItems.png";
	mlItems = GLManager::loadTexture(filename);

	backButton = new Button(1.4,.8,.5,.12);
	backButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(backButton);

    for( int i=0; i<N_MAPS; i++ ) {
		float yloc = ((N_MAPS-2)/2-i)*.22;
        mapBtns[i] = new Button(-.15,yloc,.4,.2,COLOR_OPTIONS[i][0],COLOR_OPTIONS[i][1],COLOR_OPTIONS[i][2]);
        mapBtns[i]->setTexture(mlItems,.5,1,.75,1);
        buttons.push_back(mapBtns[i]);
	}

    mapNum = 0;

	mm = upMenu;
}

MapMenu::~MapMenu() {
    delete backButton;
    for( int i=0; i<N_MAPS; i++ ) {
        delete mapBtns[i];
    }
}

void MapMenu::render() {
	GLManager::beginRender();

	glPushMatrix();

	gluLookAt(0,2,7, 0,1,0, 0,0,-1);

	GLManager::doLighting();

	glPopMatrix();

	displayOverlay();

	GLManager::endRender();
}

void MapMenu::update( float dt ) {}

void MapMenu::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: setNextState(mm, false); break;
	}
}

void MapMenu::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MapMenu::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void MapMenu::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( backButton->isActive() && backButton->testClick(mc.x, mc.y) ) {
		// Passing back user-selected map to MainMenu
		mm->setMap(mapNum);
		setNextState(mm, false);
	}
    else {
		// external click - resetting map back to default 1
		mapBtns[mapNum]->setTexture(mlItems,.5,1,.75,1);
		mapNum = 0;

        for( int i=0; i<N_MAPS; i++ ) {
			if( mapBtns[i]->isActive() && mapBtns[i]->testClick(mc.x, mc.y) ) {
				mapNum = i;
                mapBtns[i]->setTexture(mlItems,0,.5,.75,1);
                
				mb = new MapBuilder(this, mapNum);
                setNextState(mb, false);
			}
		}
    }
}

void MapMenu::mouseMoved( int dx, int dy ) {
	// if( mouseDown ) setView(dx, dy);
}