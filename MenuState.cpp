#include "MenuState.h"

MenuState::MenuState(/* GLManager* gm ): State(gm*/) {

}

MenuState::~MenuState() {

}

void MenuState::displayOverlay() {
	GLManager::switchTo2D();
	for( int i=0; i<buttons.size(); i++ ) {
		buttons[i]->display();
	}
	GLManager::switchTo3D();
}
