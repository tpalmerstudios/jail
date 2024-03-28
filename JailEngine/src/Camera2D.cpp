#include "Camera2D.h"
#include <glm/ext/matrix_transform.hpp>

namespace Jail {
Camera2D::Camera2D () :
	_screenWidth (500),
	_screenHeight (500),
	_change (true),
	_scale (1.0f),
	_position (0.0f, 0.0f),
	_cameraMatrix (1.0f),
	_orthoMatrix (1.0f)
{
}

void Camera2D::update ()
{
	if (_change)
	{
		glm::vec3 translate (-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate (_orthoMatrix, translate);

		glm::vec3 scale (_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale (glm::mat4 (1.0f), scale) * _cameraMatrix;
		
		_change = false;
	}
}

void Camera2D::init (unsigned int screenWidth, unsigned int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho (0.0f, (float) _screenWidth, 0.0f, (float) _screenHeight);
}}

