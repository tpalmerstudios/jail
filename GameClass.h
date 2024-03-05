#include <SDL2/SDL.h>
#include <GL/gl.h>

class Game
{
	private:
		SDL_Window* window;
		unsigned short int screenWidth = 1920;
		unsigned short int screenHeight = 1080;
	public:
		Game ();
		~Game ();

		int run ();
		int init ();
};
