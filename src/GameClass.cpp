#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Gameclass.h"
#include "errors.h"

/* TODO: Move Game::init () into constructor.
 * Initialize screen and Game State*/
Game::Game () : 
	sdlWidth (980), 
	sdlHeight (540), 
	gameState (GameState::PLAY), 
	shaderTime (0),
	window (nullptr)
{
}

Game::~Game ()
{
	gameState = GameState::EXIT;
}

/* Sets initial variable and gives control to gameLoop*/
void Game::run ()
{
	// Starts SDL screen
	init ();

	// Currently the sprite is the size of the screen
	sprite.init (-1.0f, -1.0f, 2.0f, 2.0f);

	// Potentially add data from a save game. Load it. Then start game loop

	// Draws Game and Processes Input
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

	initShaders ();
}

void Game::initShaders ()
{
	shaderProgram.compileShaders ("shaders/colorShading.vert", "shaders/colorShading.frag");
	shaderProgram.addAttribute ("vertexPosition");
	shaderProgram.addAttribute ("vertexColor");
	shaderProgram.linkShaders ();
}

void Game::drawGame ()
{
	glClearDepth (1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderProgram.use ();

	GLuint timeLocation = shaderProgram.getUniLoc ("time");
	glUniform1f (timeLocation, shaderTime);

	sprite.draw ();
	shaderProgram.unuse ();
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
		shaderTime += 0.1;
	}
}

