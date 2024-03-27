#ifndef GLSLSHADER_H
#define GLSLSHADER_H

#include <string>

#include <GL/glew.h>

namespace Jail
{
	class GLSLShader
	{
		public:
			// Constructor
			GLSLShader ();
			// Destructor
			~GLSLShader ();

			// Compiles Shaders from files
			void compileShaders (const std::string& vertFile, const std::string& fragFile);
			// Adds Positions and Colors to be used by shaders
			void addAttribute (const std::string& attributeName);
			// Adds them into the game file
			void linkShaders ();
			void use ();
			void unuse ();
			// Variables accessible Universally
			GLint getUniLoc (const std::string& uniformName);
		private:
			// Used as a sort of Pointer whenever using the shader
			GLuint _programID;
			GLuint _vertID;
			GLuint _fragID;
			// How many attributes are used by the shaders
			int _numAttribute;

			// Code for doing one shader. Called by compileShaders to do both
			void compileShader (const std::string& filePath, GLuint id);
	};
}
#endif // GLSLSHADER_H
