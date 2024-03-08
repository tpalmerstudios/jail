#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <vector>
#include <string>

class IOManager
{
	public:
		static bool isLoadFile (std::string sFilePath, std::vector<char>& buffer);
};
#endif // IO_MANAGER_H
