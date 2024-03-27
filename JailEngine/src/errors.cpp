/************************************
 * Errors Handler
 * TODO: Consider making this a class with a constructor and destructor
 * 
 */
#include "Errors.h"

#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>

/* Error Sent to STDOUT.
 * SDL systems quit.
 * System quit.*/
namespace Jail {
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

/*
 * class Error
 * {
 * 		public:
 * 		Error (int error)
 * 		{
 * 			std::cout
 * 		}
 * 		Error (std::string error)
 * 		{
 * 		}
 * 		~Error ();
 * 		{
 * 		SDL_Quit ();
 * 		exit (errorCode ());
 * 		}
 * 		private:
 * 		std::string errorOutput(int);
 * 		int code (std::string);
 * 		std::map errorCodes;
 * };
 */
}
