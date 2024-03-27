#include "Image_Loader.h"
#include "PicoPNG.h"
#include "Texture.h"
#include "IO_Manager.h"
#include "Errors.h"
#include <vector>

namespace Jail {
GLTexture ImageLoader::loadPNG (std::string sFilePath)
{
	GLTexture gTexture = {};
	std::vector<unsigned char> texOutput;
	std::vector<unsigned char> texInput;

	unsigned long texWidth, texHeight;

	if (IOManager::isLoadFile (sFilePath, texInput) == false)
	{
		fatalError ("Failed to load PNG file to buffer!");
	}

	int picoError = decodePNG (texOutput, texWidth, texHeight, &(texInput [0]), texInput.size ());
	if (picoError != 0)
	{
		fatalError ("Pico failed with error: " + std::to_string (picoError));
	}

	glGenTextures (1, &(gTexture.id));
	glBindTexture (GL_TEXTURE_2D, gTexture.id);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(texOutput [0]));
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap (GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, 0);
	gTexture.width = texWidth;
	gTexture.height = texHeight;
	return gTexture;
}
}
