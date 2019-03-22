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

// Trig functions for degrees
#define Cos(x) cos(3.1415926535/180*(x))
#define Sin(x) sin(3.1415926535/180*(x))

class State {
protected:
	float th = 0, ph = 20, asp = 0, fov = 55; // View settings
	void debug( std::string loc ); // Print a basic GL error message
	void Project(); // Set GL projection matrices

public:
	State( int width, int height );
	~State();

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
	void reshape( int width, int height );
};

#endif