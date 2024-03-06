#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "GameClass.h"

Game::Game ()
{
	window = nullptr;
}

Game::~Game ()
{
}

int Game::run ()
{
	init ();
	return 0;
}

int Game::init ()
{
	SDL_Init (SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow (
		"Jail Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_OPENGL);
	return 0;
}
