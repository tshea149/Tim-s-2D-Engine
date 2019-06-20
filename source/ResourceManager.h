/* Author: Tim */
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "EngineSettings.h" // for USE_RESOURCE_FILE
#include <string>
#include <memory>
#include <stdint.h>
#include <unordered_map>
#include <vector>

#if _DEBUG
static_assert(sizeof(char) == 1, "char data type larger than 1 byte.");
#endif

// This module loads files into a buffer from the resource file (if USE_RESOURCE_FILE) or loose files if not using the resource file
class ResourceManager
{
private:
	// only the AssetManager can create a ResourceManager
	friend class AssetManager;

	ResourceManager();

public:
	std::unique_ptr<std::vector<char>> loadFile(std::string filepath);
};

#endif // !FILEMANAGER_H