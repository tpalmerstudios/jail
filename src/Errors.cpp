#include "Errors.h"

#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>


void fatalError (std::string error)
{
	int input;
	std::cout << error << std::endl;
	std::cout << "Enter any key to quit...";

	std::cin >> input;
	SDL_Quit ();
	exit (1);
}

