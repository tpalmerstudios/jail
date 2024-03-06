#include <iostream>

#include "GameClass.h"

int main (int argc, char** argv)
{
	Game jail;
	jail.run ();

	std::cout << "Enter a key to quit: ";
	char wait;
	std::cin >> wait;

	return 0;
}
