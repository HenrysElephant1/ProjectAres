#include "MenuState.h"

MenuState::MenuState(/* GLManager* gm ): State(gm*/) {

}

MenuState::~MenuState() {

}

void MenuState::displayOverlay() {
	GLManager::switchTo2D();
	glDisable(GL_DEPTH_TEST);
	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->display();
	}
	for( int i=0; i<labels.size(); i++ ) {
		labels[i]->display();
	}
	glEnable(GL_DEPTH_TEST);
	GLManager::switchTo3D();
}
