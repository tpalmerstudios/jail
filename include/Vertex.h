#pragma once

#include <GL/glew.h>

struct Position
{
	float x;
	float y;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct vertex
{
	Position position;
	Color color;
};

