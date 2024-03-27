/*****************************************
 * Gameclass.h
 * Game Class Definition
 * Responsible for Input, Output, Shaders
 * The main controller of the Game
 *
 * Game State Enum Definition
 *
 * ***************/

#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>

#include <Sprite.h>
#include <GLSLShader.h>
#include <Window.h>

enum class GameState {PLAY, PAUSE, EXIT};

class Game
{
	public:
		// Constructor
		// Move init to Game ()
		Game ();
		// Destructor
		~Game ();

		// Accessible by main.cpp
		void run ();

	private:
		// Functions
		void init ();
		void processInput ();
		void drawGame ();
		void gameLoop ();
		void initShaders ();
		void calculateFPS ();

		// Variables
		Jail::Window _window;
		GameState _gameState;
		std::vector <Jail::Sprite*> _sprites;
		Jail::GLSLShader _shaderProgram;

		int _sdlWidth;
		int _sdlHeight;
		float shaderTime;
		float _fps;
		float _frameTime;
		float _maxFPS;
		
};

#endif // GAMECLASS_H
