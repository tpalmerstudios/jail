#pragma once

#include <GL/glew.h>

class Sprite
{
	public:
		Sprite ();
		~Sprite ();
		void draw ();
		void init (float spriteX, float spriteY, float spriteWidth, float spriteHeight);
	private:
		int x, y, width, height;
		GLuint vboID;
};
