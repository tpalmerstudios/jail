#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <vector>
#include <string>

#include "PicoPNG.h"

class IOManager
{
	public:
		static bool isLoadFile (std::string sFilePath, std::vector<unsigned char>& buffer);
};

#endif // IO_MANAGER_H
