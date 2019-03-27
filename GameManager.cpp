#include "GameManager.h"

GameManager::GameManager() {
	if( !init() )
		std::cout << "Game Manager failed to initialize!" << std::endl;
}

GameManager::~GameManager() {
	
}

bool GameManager::init() {
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else {
		// Use OpenGL 2.1
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

		gWindow = SDL_CreateWindow( "Project Ares", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ); // SDL_WINDOW_FULLSCREEN_DESKTOP
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else {
			gContext = SDL_GL_CreateContext( gWindow );
			if( gContext == NULL ) {
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else {
				if( SDL_GL_SetSwapInterval( 1 ) < 0 )
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );

				GLManager::setFOV(55);
				GLManager::reshape(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
				gs = new MainMenu();
			}
		}
	}

	return success;
}

void GameManager::close() {
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	SDL_Quit();
}

double GameManager::getElapsedTime() {
	Uint64 currentTime = SDL_GetPerformanceCounter();
	double deltaTime = (double)((currentTime - previousTime) * 1000 / (double)SDL_GetPerformanceFrequency());
	previousTime = currentTime;
	return deltaTime / 1000;
}

void GameManager::run() {
	SDL_Event e; // Event catcher

	// Allow keyboard inputs
	SDL_StartTextInput();

	while( !quit ) {
		// Catch events
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT )
				quit = true;
            else if( e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED ) {
            	// Resize the window
            	int sw = e.window.data1;
                int sh = e.window.data2;
                GLManager::reshape(sw, sh);
            }
			else if( e.type == SDL_KEYDOWN ) {
				// Handle a key press
				SDL_Keycode key = e.key.keysym.sym;
				gs->keyPressed( key );
			}
			else if( e.type == SDL_KEYUP ) {
				// Handle a key release
				SDL_Keycode key = e.key.keysym.sym;
				gs->keyReleased( key );
			}
			else if( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT ) {
				// Handle left mouse down
				int x = 0, y = 0;
				SDL_GetMouseState( &x, &y );
				gs->mousePressed( x, y );
			}
			else if( e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT ) {
				// Handle left mouse up
				int x = 0, y = 0;
				SDL_GetMouseState( &x, &y );
				gs->mouseReleased( x, y );
			}
			else if( e.type == SDL_MOUSEMOTION ) {
				// Handle mouse motion
				int x = 0, y = 0;
				SDL_GetMouseState( &x, &y );
				int dx = x - prevMouseX;
				int dy = y - prevMouseY;
				prevMouseX = x;
				prevMouseY = y;
				gs->mouseMoved( dx, dy );
			}
		}

		// Render and update the game
		gs->render();
		GLManager::debug("Game loop");
		gs->update( getElapsedTime() );

		// Test there is a new state to be used
		State* newState = gs->getNextState();
		if( newState != NULL ) {
			if( gs->getDeleteCurrent() )
				delete gs;
			gs = newState;

		}
		if( GLManager::QUIT )
			quit = true;
		
		// Swap double-buffered window
		SDL_GL_SwapWindow( gWindow );
	}
	
	// End keyboard inputs and close the window
	SDL_StopTextInput();
	close();
}