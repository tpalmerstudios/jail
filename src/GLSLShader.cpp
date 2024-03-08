#include <fstream>
#include <vector>
#include <string>

#include "GLSLShader.h"
#include "Errors.h"

GLSLShader::GLSLShader () : programID (0), vertID (0), fragID (0), numAttribute (0)
{
}

GLSLShader::~GLSLShader ()
{
}
void GLSLShader::addAttribute (const std::string& attributeName)
{
	glBindAttribLocation (programID, numAttribute++, attributeName.c_str());
}

GLuint GLSLShader::getUniLoc (const std::string& uniformName)
{
	GLuint location = glGetUniformLocation (programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError ("Uniform " + uniformName + " not found in shader!");
	}
	return location;
}

void GLSLShader::use ()
{
	glUseProgram (programID);
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
	programID = glCreateProgram();

	vertID = glCreateShader (GL_VERTEX_SHADER);
	if (vertID == 0)
	{
		fatalError ("Vertex Shader failed to be created");
	}
	fragID = glCreateShader (GL_FRAGMENT_SHADER);
	if (fragID == 0)
	{
		fatalError ("Fragment Shader failed to be created");
	}
	compileShader (vertFile, vertID);
	compileShader (fragFile, fragID);

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
	glAttachShader(programID, vertID);
	glAttachShader(programID, fragID);

	// Link our program
	glLinkProgram(programID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(programID);
		// Don't leak shaders either.
		glDeleteShader(vertID);
		glDeleteShader(fragID);

		std::printf ("%s\n", &errorLog[0]);
		fatalError ("Shader failed to link!");
	}

	// Always detach shaders after a successful link.
	glDetachShader(programID, vertID);
	glDetachShader(programID, fragID);
	glDeleteShader(vertID);
	glDeleteShader(fragID);
}
