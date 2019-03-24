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
#include <map>
#include <iostream>

// Trig functions for degrees
#define Cos(x) cos(3.1415926535/180*(x))
#define Sin(x) sin(3.1415926535/180*(x))

typedef struct location_struct { float x; float y; } Loc;

class GLManager {
private:
	static int screenWidth, screenHeight, fov;
	static float asp;

	static std::map<const char*, GLuint> textures; // uses map so it doesn't read a texture multiple time, just returns the GLuint

	static void project(); // Set GL projection matrices
	GLManager();

public:
	static bool QUIT;

	// GLManager( int sh, int sw, int f );
	static void setFOV( int newFOV );
	static void reshape( int width, int height ); // Window changed size

	static int getScreenWidth();
	static int getScreenHeight();

	static void beginRender();
	static void endRender();

	// Switch projection modes. switchTo3D must be preceded by a call to swtichTo2D
	static void switchTo2D();
	static void switchTo3D();

	// Load a texture and return the gl texture index
	static GLuint loadTexture( const char* filename ); //std::string & filename

	// Get coordinates in appropriate range for menu
	static Loc getMenuCoords( int x, int y );
};

#endif