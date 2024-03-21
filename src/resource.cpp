#include "Resource.h"

TextureCache Resource::_textureCache;

// TODO: change the name of GLTexture to TextStruct
GLTexture Resource::getTexture (std::string filePath)
{
	// Add error checking and statistics
	return _textureCache.getTexture (filePath);
}
