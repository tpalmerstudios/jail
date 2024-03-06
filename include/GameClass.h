#include <SDL2/SDL.h>
#include <GL/gl.h>

class Game
{
	private:
		SDL_Window* window;
		int screenWidth = 1920;
		int screenHeight = 1080;
	public:
		Game ();
		~Game ();

		int run ();
		int init ();
};
