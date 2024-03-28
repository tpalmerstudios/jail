#ifndef CAMERA2D
#define CAMERA2D

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Jail {
class Camera2D
{
	public:
		Camera2D ();

		void init (unsigned int screenWidth, unsigned int screenHeight);
		void update ();
		
		void setPosition (const glm::vec2& newPosition) { _position = newPosition; _change = true; }
		void setScale (float newScale) { _scale = newScale; _change = true;}

		glm::vec2 getPosition () { return _position; }
		glm::mat4 getCameraMatrix () { return _cameraMatrix; }
		float getScale () { return _scale; }
	private:
		unsigned int _screenWidth, _screenHeight;
		bool _change;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix, _orthoMatrix;

};}

#endif // CAMERA2D
