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
#include "Texture.h"

#include <string>

namespace Jail
{
	class Sprite
	{
		public:
			Sprite ();
			~Sprite ();
			void draw ();
			void init (float x, float y, float width, float height, std::string textPath);
		private:
			int _x, _y, _width, _height;
			GLuint _vboID;
			GLTexture _texture;
	};
}

#endif // SPRITE_H
