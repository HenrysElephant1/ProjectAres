#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL_opengl.h>

class Button {
private:
	float locx, locy, width, height; // -1 <= locy/height <= 1, -asp <= locx/width <= 1
	float colr, colg, colb; // Button color values
	GLint texture = -1;
	float u1, u2, v1, v2; // Lower and upper uv texture coordinates
public:
	Button( float x, float y, float w, float h, float r = 1.0, float g = 1.0, float b = 1.0 );
	~Button();

	void display();
	bool testClick( float x, float y );
	void setTexture( GLint tex, float ulower, float uupper, float vlower, float vupper );
};

#endif