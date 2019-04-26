#include "MapBuilder.h"

MapBuilder::MapBuilder( MapMenu* upMenu, int mNum ) {
	std::string filename = "textures/OtherMenuItems.png";
	GLuint labelsTex = GLManager::loadTexture(filename);
    filename = "textures/MapMenuButtons.png";
    GLuint buttonsTex = GLManager::loadTexture(filename);

	backButton = new Button(1.4,.8,.5,.12);
	backButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(backButton);

    saveButton = new Button(1.4,.6,.5,.12);
    saveButton->setTexture(buttonsTex,0,1,0,.25);
    buttons.push_back(saveButton);

	ml = upMenu;
    mapNum = mNum;

    map = Map::loadMap(mNum);
    viewHeight = GLManager::getMapViewHeight( map->getUnitWidth(), map->getUnitHeight() );
}

MapBuilder::~MapBuilder() {
    delete backButton;
    delete saveButton;
    delete map;
}

void MapBuilder::render() {
	GLManager::beginRender();

	glm::vec3 mapLoc = map->getCenter();
	glm::vec3 eyeLoc = mapLoc + glm::vec3(0,viewHeight,0);

	glPushMatrix();
	double Mx = mapLoc.x;
	double My = mapLoc.y;
	double Mz = mapLoc.z;
	double Ex = eyeLoc.x;
	double Ey = eyeLoc.y;
	double Ez = eyeLoc.z;
	gluLookAt(Ex,Ey,Ez, Mx,My,Mz, 0,0,-1);

    map->display();

	glPopMatrix();

	displayOverlay();

	GLManager::endRender();
}

void MapBuilder::update( float dt ) {
	// th += dt*45;
}


void MapBuilder::keyPressed( SDL_Keycode key ) {
	switch( key ) {
		case SDLK_ESCAPE: setNextState(ml, true); break;
	}
}

void MapBuilder::keyReleased( SDL_Keycode key ) {
	// switch( key ) {
	// 	case SDLK_- : break;
	// }
}

void MapBuilder::mousePressed( int x, int y ) {
	mouseDown = true;
	Loc mc = GLManager::getMenuCoords(x,y);

	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->testClick(mc.x, mc.y, true);
	}
}

void MapBuilder::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( backButton->isActive() && backButton->testClick(mc.x, mc.y) ) {
		setNextState(ml, true);
	}
    else if( saveButton->isActive() && saveButton->testClick(mc.x, mc.y) ) {
        // storing changes to map file in disk
        map->exportMap(mapNum);

        setNextState(ml, true);
    }
    else {
        int tx, ty;
        getTileClicked(x,y,tx,ty);
        std::cout << "Got Tile: " << tx << ", " << ty << std::endl;

        // toggling between Wall-tile and Floor-tile
        int oppositeTile = 1 - map->getTile(tx, ty)->getType();
        map->setTile(tx, ty, oppositeTile);
    }
}

void MapBuilder::mouseMoved( int dx, int dy ) {
	// if( mouseDown ) setView(dx, dy);
}


void MapBuilder::getTileClicked( int mx, int my, int &retTileX, int &retTileY ) {
	glm::vec3 mapLoc = map->getCenter();
	glm::vec3 eyeLoc = mapLoc + glm::vec3(0,viewHeight,0);
	glm::mat4 invPerspMat = GLManager::getInvPerspMat();
	glm::mat4 invViewMat = glm::inverse( glm::lookAt(mapLoc, eyeLoc, glm::vec3(0,0,-1)) );

	glm::vec4 ndc = GLManager::getNDC(mx,my);
	std::cout << "NDC: " << ndc.x << ", " << ndc.y << std::endl;
	glm::vec4 rayEye = invPerspMat * ndc;
	rayEye = glm::vec4(rayEye.x * .525, rayEye.y * .525, 1.0, 0.0);
	glm::vec3 rayWorld = glm::normalize(glm::vec3(invViewMat * rayEye));

	std::cout << "Ray: " << rayWorld.x << ", " << rayWorld.y << ", " << rayWorld.z << std::endl;

	float t = -eyeLoc.y / rayWorld.y;
	glm::vec3 intersection = eyeLoc + (t*rayWorld);

	std::cout << "Intersection: " << intersection.x << ", " << intersection.y << ", " << intersection.z << std::endl;

	std::cout << "mapLoc: " << mapLoc.x << ", " << mapLoc.y << ", " << mapLoc.z << std::endl;

	retTileX = floor(intersection.x / TILE_SIZE + 0.5);
	retTileY = floor(intersection.z / TILE_SIZE + 0.5);
}
