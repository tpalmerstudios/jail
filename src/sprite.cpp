#include "sprite.h"
#include "Resource.h"
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

void Sprite::init (float x, float y, float width, float height,std::string filePath)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	_texture = Resource::getTexture (filePath);

	if (_vboID == 0)
	{
		glGenBuffers (1, &_vboID);
	}
	// 2 Triangles
	Vertex vData [6];

	vData [0].setPosition (_x, _y);
	vData [0].setUV (0.0f, 0.0f);

	vData [1].setPosition (_x + width, _y);
	vData [1].setUV (1.0f, 0.0f);
	
	vData [2].setPosition (_x, _y + height);
	vData [2].setUV (0.0f, 1.0f);
	vData [3].setPosition (_x, _y + height);
	vData [3].setUV (0.0f, 1.0f);
	
	vData [4].setPosition (_x + width, _y);
	vData [4].setUV (1.0f, 0.0f);
	
	vData [5].setPosition (_x + width, _y + height);
	vData [5].setUV (1.0f, 1.0f);

	// Load colors into array
	for (int i = 0; i < 6; i++)
	{
		vData [i].setColor (255, 0, 255, 255);
	}

	vData [4].setColor (0, 0, 255, 255);
	vData [2].setColor (0x3A, 127, 255, 255);

	glBindBuffer (GL_ARRAY_BUFFER, _vboID);
	glBufferData (GL_ARRAY_BUFFER, sizeof (vData), vData, GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, 0);

}

void Sprite::draw ()
{
	glBindTexture (GL_TEXTURE_2D, _texture.id);
	glBindBuffer (GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray (0);

	// Position
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*) offsetof (Vertex, position));

	//Color
	glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (Vertex), (void*) offsetof (Vertex, color));

	glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*) offsetof (Vertex, uv));
	// Send it to to the screen
	glDrawArrays (GL_TRIANGLES, 0, 6);

	// Disable the attributes array
	glDisableVertexAttribArray (0);

	// Unbind GPU VBO
	glBindBuffer (GL_ARRAY_BUFFER, 0);
}
