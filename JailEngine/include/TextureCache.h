#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <map>
#include <string>
#include "Texture.h"

namespace Jail {
class TextureCache
{
	public:
		GLTexture getTexture (std::string filePath);
	private:
		std::map<std::string, GLTexture> _textureMap;
};}

#endif
