/**************************************
 * sprite.h
 * Author: tpalmerstudios (Tim Palmer)
 * Contact: obsoleteTiger @ protonmail.com
 * Created On: March 8, 2024
 *
 * Part of MakingGamesWithBen
 * Sprite Class
 * A major work in progress
 *************************************/

#ifndef SPRITE_H
#define SPRITE_H

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
		GLuint _vboID;
};

#endif // SPRITE_H
