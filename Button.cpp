#include "Button.h"

Button::Button( float x, float y, float w, float h, float r, float g, float b ) {
	locx = x;
	locy = y;
	width = w;
	height = h;
	colr = r;
	colg = g;
	colb = b;
}

Button::~Button() {

}

void Button::display() {
	if( texture != 0 ) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor3d(colr,colg,colb);
	glBegin(GL_QUADS);
	glTexCoord2f(u1, v1); glVertex2f(locx-width/2.0,locy-height/2.0);
	glTexCoord2f(u1, v2); glVertex2f(locx-width/2.0,locy+height/2.0);
	glTexCoord2f(u2, v2); glVertex2f(locx+width/2.0,locy+height/2.0);
	glTexCoord2f(u2, v1); glVertex2f(locx+width/2.0,locy-height/2.0);
	glEnd();
	glDisable(GL_BLEND);
	if( texture != 0 ) {
		glDisable(GL_TEXTURE_2D);
	}
}

bool Button::testClick( float x, float y, bool setActive ) {
	bool clicked = x >= locx - width/2.0 && x <= locx + width/2.0 && y >= locy - height/2.0 && y <= locy + height/2.0;
	if(clicked) active = setActive;
	else active = false;
	return clicked;
}

void Button::setTexture( GLuint tex, float ulower, float uupper, float vlower, float vupper ) {
	texture = tex;
	u1 = ulower;
	u2 = uupper;
	v1 = vlower;
	v2 = vupper;
}

bool Button::isActive() {
	return active;
}
