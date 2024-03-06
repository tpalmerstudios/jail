#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "GameClass.h"

int main (int argc, char** argv)
{
	Game jail;
	jail.run ();
	std::cout << "Enter a key to quit: ";
	int a;
	std::cin >> a;
	return 0;
}
