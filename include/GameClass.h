#include <SDL2/SDL.h>
#include <GL/glew.h>

enum class GameState {PLAY, PAUSE, EXIT};

class Game
{
	public:
		Game ();
		~Game ();

		int run ();

	private:
		// Functions
		int init ();
		int processInput ();
		int drawGame ();
		int gameLoop ();
		// Variables
		SDL_Window* window;
		GameState gameState;

		
		int sdlWidth;
		int sdlHeight;
		
};
