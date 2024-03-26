#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Gameclass.h"
#include "errors.h"

/* TODO: Move Game::init () into constructor.
 * Initialize screen and Game State*/
Game::Game () : 
	_sdlWidth (980), 
	_sdlHeight (540), 
	gameState (GameState::PLAY), 
	shaderTime (0),
	window (nullptr),
	_maxFPS (60.0f)
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
	_sprites.push_back (new Sprite ());
	_sprites.back ()->init (-1.0f, -1.0f, 1.0f, 1.0f, "textures/Enemys/Enemy_Candy1.png");

	_sprites.push_back (new Sprite ());
	_sprites.back ()->init (0.0f, -1.0f, 1.0f, 1.0f, "textures/Enemys/Enemy_Candy1.png");
	_sprites.push_back (new Sprite ());
	_sprites.back ()->init (-1.0f, 0.0f, 1.0f, 1.0f, "textures/Enemys/Enemy_Candy1.png");
	// Potentially add data from a save game. Load it. Then start game loop
	_sprites.push_back (new Sprite ());
	_sprites.back ()->init (0.0f, 0.0f, 1.0f, 1.0f, "textures/Enemys/Enemy_Candy1.png");
	//_playerTex = ImageLoader::loadPNG ("textures/Enemys/Enemy_Candy1.png");
	// Draws Game and Processes Input
	gameLoop ();
}

void Game::init ()
{
	SDL_Init (SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	window = SDL_CreateWindow (
		"Jail Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_sdlWidth,
		_sdlHeight,
		SDL_WINDOW_OPENGL );
	
	if (!window)
	{
		fatalError ("SDL Window could not be created.");
	}

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

	// V Sync 1, 0 off
	SDL_GL_SetSwapInterval (1);

	initShaders ();
}

void Game::initShaders ()
{
	shaderProgram.compileShaders ("shaders/colorShading.vert", "shaders/colorShading.frag");
	shaderProgram.addAttribute ("vertexPosition");
	shaderProgram.addAttribute ("vertexColor");
	shaderProgram.addAttribute ("vertexUV");
	shaderProgram.linkShaders ();
}

void Game::drawGame ()
{
	glClearDepth (1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderProgram.use ();

	glActiveTexture (GL_TEXTURE0);
	// glBindTexture (GL_TEXTURE_2D, _playerTex.id);
	GLint textureLocation = shaderProgram.getUniLoc ("mySampler");
	glUniform1i (textureLocation, 0);

	GLuint timeLocation = shaderProgram.getUniLoc ("time");
	glUniform1f (timeLocation, shaderTime);

	for (int i = 0; i < _sprites.size (); i ++)
	{
		_sprites [i]->draw ();
	}

	glBindTexture (GL_TEXTURE_2D, 0);
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
				// std::cout << action.motion.x << " " << action.motion.y << std::endl;
				break;
		}
	}
}

void Game::gameLoop ()
{
	while (gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks ();
		processInput ();
		shaderTime += 0.1;
		drawGame ();
		calculateFPS ();
		static int frameCount;
		frameCount++;
		if (frameCount == 60)
		{
			std::cout << _fps << std::endl;
			frameCount = 0;
		}
		float frameTicks = SDL_GetTicks () - startTicks;
		if (1000.0f / _maxFPS > frameTicks)
		{
			SDL_Delay (1000.0f / _maxFPS - frameTicks);
		}
	}
}

void Game::calculateFPS ()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes [NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks ();
	float currentTicks;
	float frameAverageTime = 0;
	int count;
	currentTicks = SDL_GetTicks ();
	_frameTime = currentTicks - prevTicks;
	prevTicks = currentTicks;
	frameTimes [currentFrame % NUM_SAMPLES] = _frameTime;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}
	for (int i = 0; i < count; i++)
	{
		frameAverageTime += frameTimes [i];
	}
	frameAverageTime /= count;
	if (frameAverageTime > 0)
	{
		_fps = 1000.0f / frameAverageTime;
	}
	else
	{
		_fps = 60.0f;
	}
}

