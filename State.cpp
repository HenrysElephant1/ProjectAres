#include "State.h"

State::State( int width, int height ) {
	reshape(width, height);
	Project();
}

State::~State() {

}

void State::update( float dt ) {

}

void State::setView( float dth, float dph ) {
	th += dth;
	ph += dph;
}

void State::reshape( int width, int height ) {
	asp = width / (float)height;
	glViewport(0,0,width,height);
}

void State::debug( std::string loc ) { 
	GLenum err;
	int i = 0;
	while((err = glGetError()) != GL_NO_ERROR)
		std::cout << "Error #" << ++i << " at " << loc << ": " << err << std::endl;
}

void State::Project() {
	// Tell OpenGL we want to manipulate the projection matrix
    glMatrixMode(GL_PROJECTION);
    // Undo previous transformations
    glLoadIdentity();
    // Perspective transformation
    gluPerspective(fov,asp,.1,100);
    // Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
}