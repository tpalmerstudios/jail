#include <fstream>
#include <vector>
#include <string>

#include "GLSLShader.h"
#include "Errors.h"

GLSLShader::GLSLShader () : _programID (0), _vertID (0), _fragID (0), numAttribute (0)
{
}

GLSLShader::~GLSLShader ()
{
}
void GLSLShader::addAttribute (const std::string& attributeName)
{
	glBindAttribLocation (_programID, numAttribute++, attributeName.c_str());
}

GLint GLSLShader::getUniLoc (const std::string& uniformName)
{
	GLint location = glGetUniformLocation (_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError ("Uniform " + uniformName + " not found in shader!");
	}
	return location;
}

void GLSLShader::use ()
{
	glUseProgram (_programID);
	for (int i = 0; i < numAttribute; i++)
	{
		glEnableVertexAttribArray (i);
	}
}

void GLSLShader::unuse ()
{
	glUseProgram (0);
	for (int i = 0; i < numAttribute; i++)
	{
		glDisableVertexAttribArray (i);
	}
}

void GLSLShader::compileShaders (const std::string& vertFile, const std::string& fragFile)
{
	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	_programID = glCreateProgram();

	_vertID = glCreateShader (GL_VERTEX_SHADER);
	if (_vertID == 0)
	{
		fatalError ("Vertex Shader failed to be created");
	}
	_fragID = glCreateShader (GL_FRAGMENT_SHADER);
	if (_fragID == 0)
	{
		fatalError ("Fragment Shader failed to be created");
	}
	compileShader (vertFile, _vertID);
	compileShader (fragFile, _fragID);

}

void GLSLShader::compileShader (const std::string& filePath, GLuint id)
{
	std::ifstream vertexStream (filePath);
	if (vertexStream.fail ())
	{
		fatalError ("Failed to open " + filePath);
	}

	std::string vertContents = "";
	std::string currentLine;

	while (std::getline (vertexStream, currentLine))
	{
		vertContents += currentLine + "\n";
	}
	vertexStream.close ();

	const char* contentPtr = vertContents.c_str ();
	glShaderSource (id, 1, &contentPtr, nullptr);

	glCompileShader (id);

	GLint success = 0;
	glGetShaderiv (id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv (id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog (maxLength);
		glGetShaderInfoLog (id, maxLength, &maxLength, &errorLog [0]);

		glDeleteShader (id);

		std::printf ("%s\n", &errorLog[0]);
		fatalError ("Shader " + filePath + " failed to compile");
		return;
	}

}

void GLSLShader::linkShaders ()
{
	// Attach our shaders to our program
	glAttachShader(_programID, _vertID);
	glAttachShader(_programID, _fragID);

	// Link our program
	glLinkProgram(_programID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(_programID);
		// Don't leak shaders either.
		glDeleteShader(_vertID);
		glDeleteShader(_fragID);

		std::printf ("%s\n", &errorLog[0]);
		fatalError ("Shader failed to link!");
	}

	// Always detach shaders after a successful link.
	glDetachShader(_programID, _vertID);
	glDetachShader(_programID, _fragID);
	glDeleteShader(_vertID);
	glDeleteShader(_fragID);
}
