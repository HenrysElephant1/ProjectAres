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

class State {
protected:
	float th = 0, ph = 20, asp = 0, fov = 55;
	void debug( std::string loc ); // Print a basic GL error message
	void Project();

public:
	State( int width, int height );
	~State();
	virtual void render() = 0;
	virtual void update( float dt ) = 0;

	void setView( float th, float ph );
	void reshape( int width, int height );
};

#endif