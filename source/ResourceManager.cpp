#include "ResourceManager.h"
#include <fstream>

#define RESOURCE_FILE "resource.dat"

ResourceManager::ResourceManager()
{
#if USE_RESOURCE_FILE
	// load resource archive
#endif
}

std::unique_ptr<std::vector<char>> ResourceManager::loadFile(std::string filepath)
{
#if 0 == USE_RESOURCE_FILE
	// load directly from loose file
	std::ifstream read_f(filepath, std::ios::binary);
	if (read_f.is_open())
	{
		// read in file to vector
		std::unique_ptr<std::vector<char>> p_data = std::make_unique<std::vector<char>>((std::istreambuf_iterator<char>(read_f)), std::istreambuf_iterator<char>());
		return p_data;
	}
	else
		return nullptr;

#else
	// TODO: read from resource file
	return nullptr;

#endif
}
