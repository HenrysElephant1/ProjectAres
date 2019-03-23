#include "State.h"

State::State() {
	
}

State::~State() {
}

void State::update( float dt ) {

}

void State::setView( float dth, float dph ) {
	th += dth;
	ph += dph;
}

void State::debug( std::string loc ) { 
	GLenum err;
	int i = 0;
	while((err = glGetError()) != GL_NO_ERROR)
		std::cout << "Error #" << ++i << " at " << loc << ": " << err << std::endl;
}

void State::setNextState( State* newState ) {
	nextState = newState;
}

State* State::getNextState() {
	State* toReturn = nextState;
	nextState = NULL;
	return toReturn;
}
