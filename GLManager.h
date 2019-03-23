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
	static int screenWidth, screenHeight, fov;
	static float asp;

	static void project(); // Set GL projection matrices
	GLManager();

public:
	// GLManager( int sh, int sw, int f );
	static void setFOV( int newFOV );
	static void reshape( int width, int height ); // Window changed size

	static int getScreenWidth();
	static int getScreenHeight();

	static void switchTo2D();
	static void switchTo3D();

	static void clear();
};

#endif