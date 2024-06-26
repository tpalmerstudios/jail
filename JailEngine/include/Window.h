#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <string>

namespace Jail {
enum windowFlags {
	NO_FLAGS = 0x0,
	INVISIBLE = 0x1,
	FULLSCREEN = 0x2,
	BORDERLESS = 0x4
};

class Window
{
	public:
		Window ();
		int create (const std::string &windowName, unsigned int screenWidth, unsigned int screenHeight, unsigned int currentFlags);
		void swapBuffer ();

		unsigned int getScreenWidth () {return _screenWidth;}
		unsigned int getScreenHeight () {return _screenHeight;}
	private:
		SDL_Window* _sdlWindow;
		unsigned int _screenWidth, _screenHeight;
};}
#endif // WINDOW_H
