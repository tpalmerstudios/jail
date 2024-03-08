#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <vector>
#include <string>

#include "texture.h"
#include "PicoPNG.h"

class IOManager
{
	public:
		static bool isLoadFile (std::string sFilePath, std::vector<unsigned char>& buffer);
};

class ImageLoader
{
	GLTexture loadPNG (std::string sFilePath);
}
#endif // IO_MANAGER_H
