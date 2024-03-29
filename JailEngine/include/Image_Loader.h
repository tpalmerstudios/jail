#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <string>
#include "Texture.h"

namespace Jail
{
	class ImageLoader
	{
		public:
			static GLTexture loadPNG (std::string sFilePath);
	};
}

#endif // IMAGE_LOADER_H
