#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Gameclass.h"
#include <Jail.h>
#include <Camera2D.h>
#include <Errors.h>

/* TODO: Move Game::init () into constructor.
 * Initialize screen and Game State*/
Game::Game () : 
	_sdlWidth (980), 
	_sdlHeight (540), 
	_gameState (GameState::PLAY), 
	shaderTime (0),
	_maxFPS (60.0f)
{
	_camera.init (_sdlWidth, _sdlHeight);
}

Game::~Game ()
{
	_gameState = GameState::EXIT;
}

/* Sets initial variable and gives control to gameLoop*/
void Game::run ()
{
	// Starts SDL screen
	init ();

	// Currently the sprite is the size of the screen
	_sprites.push_back (new Jail::Sprite ());
	_sprites.back ()->init (0.0f, 0.0f, (float) _sdlWidth / 2, (float) _sdlHeight / 2, "textures/Enemys/Enemy_Candy1.png");

	_sprites.push_back (new Jail::Sprite ());
	_sprites.back ()->init ((float) _sdlWidth / 2, 0.0f, (float) _sdlWidth / 2, (float) _sdlHeight / 2, "textures/Enemys/Enemy_Candy1.png");

	_sprites.push_back (new Jail::Sprite ());
	_sprites.back ()->init (0.0f, (float) _sdlHeight / 2, (float) _sdlWidth / 2, (float) _sdlHeight / 2, "textures/Enemys/Enemy_Candy1.png");
	// Potentially add data from a save game. Load it. Then start game loop
	_sprites.push_back (new Jail::Sprite ());
	_sprites.back ()->init ((float) _sdlWidth / 2, (float) _sdlHeight / 2, (float) _sdlWidth / 2, (float) _sdlHeight / 2, "textures/Enemys/Enemy_Candy1.png");
	//_playerTex = ImageLoader::loadPNG ("textures/Enemys/Enemy_Candy1.png");
	// Draws Game and Processes Input
	gameLoop ();
}

void Game::init ()
{
	Jail::init ();
	_window.create ("Jail Engine", _sdlWidth, _sdlHeight, 0);

	initShaders ();
}

void Game::initShaders ()
{
	_shaderProgram.compileShaders ("shaders/colorShading.vert", "shaders/colorShading.frag");
	_shaderProgram.addAttribute ("vertexPosition");
	_shaderProgram.addAttribute ("vertexColor");
	_shaderProgram.addAttribute ("vertexUV");
	_shaderProgram.linkShaders ();
}

void Game::drawGame ()
{
	glClearDepth (1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	_shaderProgram.use ();

	glActiveTexture (GL_TEXTURE0);
	// glBindTexture (GL_TEXTURE_2D, _playerTex.id);
	GLint textureLocation = _shaderProgram.getUniLoc ("mySampler");
	glUniform1i (textureLocation, 0);

	GLuint timeLocation = _shaderProgram.getUniLoc ("time");
	glUniform1f (timeLocation, shaderTime);

	GLuint projectionLocation = _shaderProgram.getUniLoc ("projection");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix ();
	glUniformMatrix4fv (projectionLocation, 1, GL_FALSE, &(cameraMatrix [0] [0]));

	for (unsigned long i = 0; i < _sprites.size (); i ++)
	{
		_sprites [i]->draw ();
	}

	glBindTexture (GL_TEXTURE_2D, 0);
	_shaderProgram.unuse ();
	/***************************************************
	glEnableClientState (GL_COLOR_ARRAY);
	glBegin (GL_TRIANGLES);
	glColor3f (1.0f, 0.0f, 0.0f);

	glVertex2f (0, 0);
	glVertex2f (0, 1);
	glVertex2f (-1, 1);
	glEnd ();
	**************************************************/

	_window.swapBuffer ();
}

void Game::processInput ()
{
	SDL_Event action;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent (&action))
	{
		switch (action.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;

			case SDL_MOUSEMOTION:
				//std::cout << action.motion.x << " " << action.motion.y << std::endl;
				break;
			case SDL_KEYDOWN:
				switch (action.key.keysym.sym)
				{
					case SDLK_w:
						_camera.setPosition (_camera.getPosition () + glm::vec2(0.0, CAMERA_SPEED));
						break;
					case SDLK_s:
						_camera.setPosition (_camera.getPosition () + glm::vec2(0.0, -CAMERA_SPEED));
						break;
					case SDLK_a:
						_camera.setPosition (_camera.getPosition () + glm::vec2(-CAMERA_SPEED, 0.0f));
						break;
					case SDLK_d:
						_camera.setPosition (_camera.getPosition () + glm::vec2(CAMERA_SPEED, 0.0f));
						break;
					case SDLK_q:
						_camera.setScale (_camera.getScale () + SCALE_SPEED);
						break;
					case SDLK_e:
						_camera.setScale (_camera.getScale () - SCALE_SPEED);
						break;
				}
				break;
		}
	}
}

void Game::gameLoop ()
{
	while (_gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks ();
		processInput ();
		shaderTime += 0.1;
		_camera.update ();
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
	static const unsigned char NUM_SAMPLES = 10;
	static unsigned char currentFrame = 0;
	static float frameTimes [NUM_SAMPLES];
	static float prevTicks = SDL_GetTicks ();

	float frameAverageTime = 0;
	float currentTicks;
	unsigned char count;

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
	for (unsigned char i = 0; i < count; i++)
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

