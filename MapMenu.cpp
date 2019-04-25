#include "MapMenu.h"

MapMenu::MapMenu( MainMenu *upMenu, Map *m ) {
	std::string filename = "textures/OtherMenuItems.png";
	GLuint labelsTex = GLManager::loadTexture(filename);

	backButton = new Button(0,.7,1,.25);
	backButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(backButton);

	createMapButton = new Button(0,.7,1,.25);
	createMapButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(createMapButton);

	loadMapButton = new Button(0,.7,1,.25);
	loadMapButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(loadMapButton);

	editMapButton = new Button(0,.7,1,.25);
	editMapButton->setTexture(labelsTex,0,1,.5,.75);
	buttons.push_back(editMapButton);

	mm = upMenu;
	map = m;

	viewHeight = GLManager::getMapViewHeight( map->getUnitWidth(), map->getUnitHeight() );
}

MapMenu::~MapMenu() {

}

void MapMenu::render() {
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

	GLManager::doLighting();

	map->display();

	glPopMatrix();

	displayOverlay();

	GLManager::endRender();
}

void MapMenu::update( float dt ) {
	// th += dt*45;
}

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

	int tx, ty;
	getTileClicked(x,y,tx,ty);
	std::cout << "Got Tile: " << tx << ", " << ty << std::endl;
}

void MapMenu::mouseReleased( int x, int y ) {
	mouseDown = false;
	Loc mc = GLManager::getMenuCoords(x,y);

	if( backButton->isActive() && backButton->testClick(mc.x, mc.y) ) {
		setNextState(mm, false);
	}
}

void MapMenu::mouseMoved( int dx, int dy ) {
	// if( mouseDown ) setView(dx, dy);
}

void MapMenu::getTileClicked( int mx, int my, int &retTileX, int &retTileY ) {
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
