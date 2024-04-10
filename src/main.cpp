#include <iostream>

#include "Gameclass.h"

int main (int argc, char** argv)
{
	Game jail;
	char wait;

	jail.run ();

	std::cout << "Enter a key to quit: ";
	std::cin >> wait;

	return 0;
}
