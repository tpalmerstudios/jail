#include "Resource.h"

namespace Jail {
TextureCache Resource::_textureCache;

// TODO: change the name of GLTexture to TextStruct
GLTexture Resource::getTexture (const std::string &filePath)
{
	// Add error checking and statistics
	return _textureCache.getTexture (filePath);
}
}

