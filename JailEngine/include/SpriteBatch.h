#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"


namespace Jail {

	struct Glyph
	{
		GLuint texture;
		float depth;
		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class SpriteBatch
	{
		public:
			void init ();
			void begin ();
			void draw (glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, Color color);
			void end ();

			void renderBatch ();

		private:
			GLuint _vbo;
			GLuint _vao;

	};
}

#endif // SPRITEBATCH_H
