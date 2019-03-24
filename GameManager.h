#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

#include "GLManager.h"
#include "MainMenu.h"

#define DEFAULT_SCREEN_WIDTH 1400
#define DEFAULT_SCREEN_HEIGHT 900

class GameManager {
private:
	// The gamestate
	State* gs;

	// Window management variables
	SDL_Window* gWindow = NULL;
	SDL_GLContext gContext;

	// Game control variables
	Uint64 previousTime = 0;
	int prevMouseX = 0, prevMouseY = 0;
	bool quit = false;

	bool init(); // Initialize SDL and OpenGL context
	void close(); // Close the window
	double getElapsedTime(); // Get time since last frame in seconds

public:
	GameManager();
	~GameManager();
	void run();
};

#endif