#include <iostream>

#include "TextureCache.h"
#include "Image_Loader.h"

namespace Jail {
GLTexture TextureCache::getTexture (std::string filePath)
{
	// map iterator
	// std::map<std::string, GLTexture>::iterator mapI =_textureMap.find (filePath);
	auto mapI =_textureMap.find (filePath);
	if (mapI == _textureMap.end ())
	{
		// Please add error checking here
		GLTexture newTexture = ImageLoader::loadPNG (filePath);
		// std::pair<std::string, GLTexture> newPair (filePath, newTexture);
		_textureMap.insert (make_pair (filePath, newTexture));

		std::cout << "Loaded Texture" << std::endl;
		return newTexture;
	}
	std::cout << "Used Cached Texture" << std::endl;
	return mapI->second;
}
}

