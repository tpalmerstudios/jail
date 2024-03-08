#include "errors.h"

#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>

/* Error Sent to STDOUT.
 * SDL systems quit.
 * System quit.*/
void fatalError (std::string error)
{
	// This allows pause to see final frame before exit
	char input;
	std::cout << "FATAL ERROR: " + error << std::endl;
	std::cout << "Enter any key to quit...";

	std::cin >> input;
	SDL_Quit ();
	exit (1);
}

