#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#define Cos(x) cos(3.1415926535/180*(x))
#define Sin(x) sin(3.1415926535/180*(x))

class GameState: public State {
private:

public:
	GameState( int width, int height );
	~GameState();
	void render();
	void update( float dt );
};

#endif