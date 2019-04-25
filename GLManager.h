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
#include <cmath>

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>

// Trig functions for degrees
#define Cos(x) cos(3.1415926535/180*(x))
#define Sin(x) sin(3.1415926535/180*(x))
#define Tan(x) tan(3.1415926535/180*(x))
#define Atan(x) (atan(x)*180/3.1415926535)

#define NEAR_PLANE 1
#define FAR_PLANE 500

typedef struct location_struct { float x; float y; } Loc;

class GLManager {
private:
	static int screenWidth, screenHeight, fov;
	static float asp;

	static std::map<std::string, GLuint> textures; // uses map so it doesn't read a texture multiple time, just returns the GLuint

	static void project(); // Set GL projection matrices
	GLManager();

	static GLuint loadShaderFromFile(GLenum type, const char* filename);

public:
	static bool QUIT;
	static GLuint lightingShader;

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
	static GLuint loadTexture( std::string & filename ); //std::string & filename

	// Get coordinates in appropriate range for menu
	static Loc getMenuCoords( int x, int y );

	static void debug( std::string loc ); // Print a basic GL error message
	static GLuint createProgram(const char* vertexShader, const char* fragShader);

	static float getMapViewHeight( float width, float height ); // Return a view height based on map and window dimensions
	static glm::mat4 getInvPerspMat(); // Return inverse of perspective matrix
	static glm::vec4 getNDC( int mx, int my ); // Return Normalized Device Coordinates from mouse position

	static void doLighting( float posx = 100.0, float posy = 100.0, float posz = 0.0 );
};

#endif