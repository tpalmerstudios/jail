#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Sprite.h"

enum class GameState {PLAY, PAUSE, EXIT};

class Game
{
	public:
		Game ();
		~Game ();

		void run ();

	private:
		// Functions
		void init ();
		void processInput ();
		void drawGame ();
		void gameLoop ();
		// Variables
		SDL_Window* window;
		GameState gameState;
		Sprite sprite;

		
		int sdlWidth;
		int sdlHeight;
		
};
