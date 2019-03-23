#include "GLManager.h"

GLManager::GLManager(){}

int GLManager::screenWidth;
int GLManager::screenHeight;
int GLManager::fov;
float GLManager::asp;

// GLManager::GLManager( int sw, int sh, int f ) {
// 	fov = f;
// 	reshape(sw,sh);
// }

void GLManager::setFOV( int newFOV ) {
	fov = newFOV;
	project();
}

void GLManager::reshape( int width, int height ) {
	screenWidth = width;
	screenHeight = height;
	asp = width / (float)height;
	project();
	glViewport(0,0,width,height);
}

void GLManager::project() {
	// Tell OpenGL we want to manipulate the projection matrix
    glMatrixMode(GL_PROJECTION);
    // Undo previous transformations
    glLoadIdentity();
    // Perspective transformation
    gluPerspective(fov,asp,.1,100);
    // Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
}

int GLManager::getScreenWidth() {
	return screenWidth;
}

int GLManager::getScreenHeight() {
	return screenHeight;
}

void GLManager::clear() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLManager::switchTo2D() {
	// Save projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-asp,asp,-1,1,-1,1); // Create orthogonal view with coordinates -asp <= x <= asp, -1 <= y <= 1
	// Save modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void GLManager::switchTo3D() {
	// Return to previously saved projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	// Return to previously saved modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
