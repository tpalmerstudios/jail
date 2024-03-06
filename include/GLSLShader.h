#pragma once

#include <string>

#include <GL/glew.h>

class GLSLShader
{
	public:
		GLSLShader ();
		~GLSLShader ();

		void compileShaders (const std::string& vertFile, const std::string& fragFile);
		void addAttribute (const std::string& attributeName);
		void linkShaders ();
		void use ();
		void unuse ();
	private:
		GLuint programID;
		GLuint vertID;
		GLuint fragID;
		int numAttribute;
		void compileShader (const std::string& filePath, GLuint id);
};
