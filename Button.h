#ifndef BUTTON_H
#define BUTTON_H

#include "GLManager.h"

class Button {
private:
	float locx, locy, width, height; // -1 <= locy <= 1, -asp <= locx <= asp
	float colr, colg, colb; // Button color values
	GLuint texture = 0;
	GLuint activeTexture = 0;
	float u1, u2, v1, v2; // Lower and upper uv texture coordinates
	float au1, au2, av1, av2; // Lower and upper active uv texture coordinates
	bool active = false; // Is the button currently being pressed?

public:
	Button( float x, float y, float w, float h, float r = 0.20, float g = 0.40, float b = 0.10 );
	~Button();

	void display();
	bool testClick( float x, float y, bool setActive = false );
	void setTexture( GLuint tex, float ulower, float uupper, float vlower, float vupper );
	void setActiveTexture( GLuint tex, float ulower, float uupper, float vlower, float vupper );
	bool isActive();
};

#endif