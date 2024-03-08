#include <fstream>
#include "IO_Manager.h"

bool IOManager::isLoadFile (std::string sFilePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file (sFilePath, std::ios::binary);
	if (file.fail ())
	{
		perror (sFilePath.c_str ());
		return false;
	}

	// Seek the end
	file.seekg (0, std::ios::end);
	// Size of the file
	int iFileSize = file.tellg ();
	// Go to the beginning
	file.seekg (0, std::ios::beg);

	// Not the file Header
	iFileSize -= file.tellg ();

	buffer.resize (iFileSize);

	// Hacky
	file.read ((char *)&(buffer [0]), iFileSize);
	file.close ();
	return true;
}

