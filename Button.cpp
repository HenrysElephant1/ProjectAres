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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor3d(colr,colg,colb);

	GLuint useTex;
	float lu, uu, lv, uv;
	if( active && activeTexture != 0 ) {
		useTex = activeTexture; lu = au1; uu = au2; lv = av1; uv = av2;
	}
	else {
		useTex = texture; lu = u1; uu = u2; lv = v1; uv = v2;
	}

	glBindTexture(GL_TEXTURE_2D, useTex);
	glBegin(GL_QUADS);
	glTexCoord2f(lu, lv); glVertex2f(locx-width/2.0,locy-height/2.0);
	glTexCoord2f(lu, uv); glVertex2f(locx-width/2.0,locy+height/2.0);
	glTexCoord2f(uu, uv); glVertex2f(locx+width/2.0,locy+height/2.0);
	glTexCoord2f(uu, lv); glVertex2f(locx+width/2.0,locy-height/2.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

bool Button::testClick( float x, float y, bool setActive ) {
	bool clicked = x >= locx - width/2.0 && x <= locx + width/2.0 && y >= locy - height/2.0 && y <= locy + height/2.0;
	if(clicked) active = setActive;
	else active = false;
	return clicked;
}

void Button::setTexture( GLuint tex, float ulower, float uupper, float vlower, float vupper ) {
	// uv coordinates range from 0 to 1 and represent the x and y coordinates of the texture edges where (0,0) is the bottom left corner
	// Ex: ulower = 0, uupper = 1, vlower = .75, and vupper = 1 would texture the button using the top
	// quarter of the texture passed in
	texture = tex;
	u1 = ulower;
	u2 = uupper;
	v1 = vlower;
	v2 = vupper;
}

// Optional texture to display when button is being pressed (Not really used right now)
void Button::setActiveTexture( GLuint tex, float ulower, float uupper, float vlower, float vupper ) {
	activeTexture = tex;
	au1 = ulower;
	au2 = uupper;
	av1 = vlower;
	av2 = vupper;
}

bool Button::isActive() {
	return active;
}
