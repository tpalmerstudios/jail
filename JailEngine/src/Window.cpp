#include "Window.h"
#include "Errors.h"

void Window::swapBuffer ()
{
	SDL_GL_SwapWindow (_sdlWindow);
}

int Window::create (std::string windowName, unsigned int screenWidth, unsigned int screenHeight, unsigned int currentFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (currentFlags & INVISIBLE)
	{
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}
	_sdlWindow = SDL_CreateWindow (
		windowName.c_str (),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth,
		screenHeight,
		flags);
	
	if (!_sdlWindow)
	{
		fatalError ("SDL Window could not be created.");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext (_sdlWindow);
	if (!glContext)
	{
		fatalError ("SDL_GL context could not be created!");
	}

	GLenum error = glewInit ();
	if (error != GLEW_OK)
	{
		fatalError ("Could not initialize glew");
	}

	std::printf ("*** OpenGL Version: %s\n", glGetString (GL_VERSION));
	glClearColor (0.0f,0.0f,0.0f,1.0f);

	// V Sync 1, 0 off
	SDL_GL_SetSwapInterval (1);

	return 0;
}
