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

void State::setNextState( State* newState, bool deleteSelf ) {
	nextState = newState;
	deleteCurrent = deleteSelf;
}

State* State::getNextState() {
	State* toReturn = nextState;
	nextState = NULL;
	return toReturn;
}

bool State::getDeleteCurrent() {
	return deleteCurrent;
}
