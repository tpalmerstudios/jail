#ifndef RESOURCE_CACHE_H
#define RESOURCE_CACHE_H

#include "TextureCache.h"
#include <string>

namespace Jail
{
	class Resource
	{
		public:
			static GLTexture getTexture (std::string filePath);
			//static GLuint boundTexture;
		private:
			static TextureCache _textureCache;

	};
}

#endif // RESOURCE_CACHE_H
