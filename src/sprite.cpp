#include "sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite ()
{
	_vboID = 0;
}
/* Alternat Sprite ()
 * Sprite::Sprite (float x, float y, float width, float width) : _vboID (0)
 * {
 * 	glGenBuffers (1, &_vboID);
 * 	if (_vboID == 0)
 * 		fatalError ("Buffer could not be created");
 *
 *
 * }
 *
*/
Sprite::~Sprite ()
{
	if (_vboID != 0)
		glDeleteBuffers (1, &_vboID);
}

void Sprite::init (float spriteX, float spriteY, float spriteWidth, float spriteHeight)
{
	x = spriteX;
	y = spriteY;
	width = spriteWidth;
	height = spriteHeight;

	if (_vboID == 0)
	{
		glGenBuffers (1, &_vboID);
	}
	// 2 Triangles
	vertex vData [6];

	// Triangle 1
	vData [0].position.x = x;
	vData [0].position.y = y;

	vData [1].position.x = x + width;
	vData [1].position.y = y;

	vData [2].position.x = x;
	vData [2].position.y = y + height;

	// Triagle 2 
	// 2 & 3 are the same
	vData [3].position.x = x;
	vData [3].position.y = y + height;

	// 1 & 4 are the same
	vData [4].position.x = x + width;
	vData [4].position.y = y;

	vData [5].position.x = x + width;
	vData [5].position.y = y + height;

	// Load colors into array
	for (int i = 0; i < 6; i++)
	{
		vData [i].color.r = 255;
		vData [i].color.g = 0;
		vData [i].color.b = 255;
		vData [i].color.a = 255;
	}

	vData [1].color.r = 0;
	vData [4].color.r = 0;
	vData [2].color.g = 127;
	vData [3].color.g = 127;

	glBindBuffer (GL_ARRAY_BUFFER, _vboID);
	glBufferData (GL_ARRAY_BUFFER, sizeof (vData), vData, GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, 0);

}

void Sprite::draw ()
{
	glBindBuffer (GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray (0);

	// Position
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (vertex), (void*) offsetof (vertex, position));

	//Color
	glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (vertex), (void*) offsetof (vertex, color));

	// Send it to to the screen
	glDrawArrays (GL_TRIANGLES, 0, 6);

	// Disable the attributes array
	glDisableVertexAttribArray (0);

	// Unbind GPU VBO
	glBindBuffer (GL_ARRAY_BUFFER, 0);
}
