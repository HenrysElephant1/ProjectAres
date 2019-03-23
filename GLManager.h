#ifndef GLMANAGER_H
#define GLMANAGER_H

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

class GLManager {
private:
	int screenWidth, screenHeight, fov;
	float asp;

	void project(); // Set GL projection matrices
public:
	GLManager( int sh, int sw, int f );
	void reshape( int width, int height ); // Window changed size

	int getScreenWidth();
	int getScreenHeight();

	void setFOV( int newFOV );

	static void clear();
};

#endif