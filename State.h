#ifndef STATE_H
#define STATE_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <iostream>

#include "GLManager.h"

class State {
protected:
	// GLManager* g;

	float th = 0, ph = 20; // View settings
	bool mouseDown = false;

	State* nextState = NULL;
	bool deleteCurrent = false;

	void setNextState( State* newState, bool deleteSelf ); // Set the state for main to use

public:
	State(/* GLManager* gm */);
	virtual ~State();

	// Functions to be implemented by derived class
	virtual void render() = 0;
	virtual void update( float dt ) = 0;

	// Handlers to be implemented by derived class
	virtual void keyPressed( SDL_Keycode key ) = 0; 
	virtual void keyReleased( SDL_Keycode key ) = 0; 
	virtual void mousePressed( int x, int y ) = 0; 
	virtual void mouseReleased( int x, int y ) = 0; 
	virtual void mouseMoved( int dx, int dy ) = 0; 

	// Window controls
	void setView( float th, float ph );

	// Function to allow main to get the next state
	State* getNextState();
	bool getDeleteCurrent();
};

#endif