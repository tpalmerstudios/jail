#include "Sprite.h"

Sprite::Sprite ()
{
	vboID = 0;
}

Sprite::~Sprite ()
{
	if (vboID != 0)
		glDeleteBuffers (1, &vboID);
}

void Sprite::init (float spriteX, float spriteY, float spriteWidth, float spriteHeight)
{
	x = spriteX;
	y = spriteY;
	width = spriteWidth;
	height = spriteHeight;

	if (vboID == 0)
	{
		glGenBuffers (1, &vboID);
	}
	float vertices [6 * 2];
	vertices [0] = x;
	vertices [4] = x;
	vertices [6] = x;

	vertices [1] = y;
	vertices [3] = y;
	vertices [9] = y;

	vertices [2] = x + width;
	vertices [8] = x + width;
	vertices [10] = x + width;
	
	vertices [5] = y + height;
	vertices [7] = y + height;
	vertices [11] = y + height;

	glBindBuffer (GL_ARRAY_BUFFER, vboID);
	glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, 0);

}

void Sprite::draw ()
{
	glBindBuffer (GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray (0);

	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays (GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, 0);
}
