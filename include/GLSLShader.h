#ifndef GLSLSHADER_H
#define GLSLSHADER_H

#include <string>

#include <GL/glew.h>

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
		GLuint _programID;
		GLuint _vertID;
		GLuint _fragID;
		int numAttribute;


		void compileShader (const std::string& filePath, GLuint id);
};

#endif // GLSLSHADER_H
