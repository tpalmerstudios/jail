#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "GameClass.h"

void fatalError (std::string error)
{
	int input;
	std::cout << error << std::endl;
	std::cout << "Enter any key to quit...";

	std::cin >> input;
	SDL_Quit ();
}

Game::Game ()
{
	window = nullptr;
	sdlWidth = 980;
	sdlHeight = 540;
	gameState = GameState::PLAY;
}

Game::~Game ()
{
	gameState = GameState::EXIT;
}

void Game::run ()
{
	init ();
	gameLoop ();
}

void Game::init ()
{
	SDL_Init (SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow (
		"Jail Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		sdlWidth,
		sdlHeight,
		SDL_WINDOW_OPENGL );
	
	if (!window)
	{
		fatalError ("SDL Window could not be created.");
	}

	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	SDL_GLContext glContext = SDL_GL_CreateContext (window);
	if (!glContext)
	{
		fatalError ("SDL_GL context could not be created!");
	}

	GLenum error = glewInit ();
	if (error != GLEW_OK)
	{
		fatalError ("Could not initialize glew");
	}

	glClearColor (0.0f,0.0f,0.0f,1.0f);
}

void Game::drawGame ()
{
	glClearDepth (1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/***************************************************
	glEnableClientState (GL_COLOR_ARRAY);
	glBegin (GL_TRIANGLES);
	glColor3f (1.0f, 0.0f, 0.0f);

	glVertex2f (0, 0);
	glVertex2f (0, 1);
	glVertex2f (-1, 1);
	glEnd ();
	**************************************************/

	SDL_GL_SwapWindow (window);
}

void Game::processInput ()
{
	SDL_Event action;
	while (SDL_PollEvent (&action))
	{
		switch (action.type)
		{
			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;

			case SDL_MOUSEMOTION:
				std::cout << action.motion.x << " " << action.motion.y << std::endl;
				break;
		}
	}
}

void Game::gameLoop ()
{
	while (gameState != GameState::EXIT)
	{
		processInput ();
		drawGame ();
	}
}

